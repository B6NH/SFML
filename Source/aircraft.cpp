#include "../Header/aircraft.h"
//#include "../Header/category.h"
#include "../Header/data_tables.h"
#include "../Header/utility.h"
#include "../Header/pickup.h"
#include "../Header/command_queue.h"
#include "../Header/resource_holder.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <cmath>


// Initialize table with Aircraft data in anonymous namespace
namespace{
	const std::vector<AircraftData> Table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.get(Table[type].texture))
, mFireCommand()
, mMissileCommand()
, mFireCountdown(sf::Time::Zero)
, mIsFiring(false)
, mIsLaunchingMissile(false)
, mIsMarkedForRemoval(false)
, mFireRateLevel(1)
, mSpreadLevel(1)
, mMissileAmmo(2)
, mDropPickupCommand()
, mTravelledDistance(0.f)
, mDirectionIndex(0)
, mHealthDisplay(nullptr)
, mMissileDisplay(nullptr){

	centerOrigin(mSprite);

	// Create bullets
	mFireCommand.category = Category::SceneAirLayer;
	mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time){
		createBullets(node, textures);
	};

	// Create missile
	mMissileCommand.category = Category::SceneAirLayer;
	mMissileCommand.action = [this, &textures] (SceneNode& node, sf::Time){
		createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
	};

	mDropPickupCommand.category = Category::SceneAirLayer;
	mDropPickupCommand.action = [this, &textures] (SceneNode& node, sf::Time){
		createPickup(node, textures);
	};

	// Create health display and attach it to aircraft
	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	// Show number of missiles for player aircraft
	if (getCategory() == Category::PlayerAircraft){
		std::unique_ptr<TextNode> missileDisplay(new TextNode(fonts, ""));
		missileDisplay->setPosition(0, 70);
		mMissileDisplay = missileDisplay.get();
		attachChild(std::move(missileDisplay));
	}

	updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands){

	if (isDestroyed()){
		checkPickupDrop(commands);
		mIsMarkedForRemoval = true;
		return;
	}

	checkProjectileLaunch(dt, commands);

	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	updateTexts();
}

unsigned int Aircraft::getCategory() const{
	if (isAllied()){
		return Category::PlayerAircraft;
	}else{
		return Category::EnemyAircraft;
	}
}

sf::FloatRect Aircraft::getBoundingRect() const{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Aircraft::isMarkedForRemoval() const{
	return mIsMarkedForRemoval;
}

bool Aircraft::isAllied() const{
	return mType == Eagle;
}

float Aircraft::getMaxSpeed() const{
	return Table[mType].speed;
}

void Aircraft::increaseFireRate(){
	if(mFireRateLevel < 10){
		++mFireRateLevel;
	}
}

void Aircraft::increaseSpread(){
	if(mSpreadLevel < 3){
		++mSpreadLevel;
	}
}

void Aircraft::collectMissiles(unsigned int count){
	mMissileAmmo += count;
}

void Aircraft::fire(){
	if (Table[mType].fireInterval != sf::Time::Zero){
		mIsFiring = true;
	}
}

void Aircraft::launchMissile(){
	if(mMissileAmmo > 0){
		mIsLaunchingMissile = true;
		--mMissileAmmo;
	}
}

void Aircraft::updateMovementPattern(sf::Time dt){

	// Find directions for current aircraft.
	const std::vector<Direction> & directions = Table[mType].directions;

	// Proceed if directions are found.
	if (!directions.empty()){

		// If travelled distance for current direction was passed set next direction
		// from pattern and change travelled distance to 0.
		if (mTravelledDistance > directions[mDirectionIndex].distance){
			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}

		// Calculate velocity vector from angle
		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		// Set velocity
		setVelocity(vx, vy);

		// Update travelled distance
		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
	}
}

// Drop pickups
void Aircraft::checkPickupDrop(CommandQueue& commands){
	if (!isAllied() && randomInt(3) == 0){
		commands.push(mDropPickupCommand);
	}
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands){

	// Enemy always fires
	if(!isAllied()){
		fire();
	}

	if(mIsFiring && mFireCountdown <= sf::Time::Zero){
		commands.push(mFireCommand);
		mFireCountdown += Table[mType].fireInterval / (mFireRateLevel + 1.f);
		mIsFiring = false;
	}else if (mFireCountdown > sf::Time::Zero){
		mFireCountdown -= dt;
		mIsFiring = false;
	}

	if (mIsLaunchingMissile){
		commands.push(mMissileCommand);
		mIsLaunchingMissile = false;
	}
}

void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const{

	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (mSpreadLevel){
		case 1:
			createProjectile(node, type, 0.0f, 0.5f, textures);
			break;

		case 2:
			createProjectile(node, type, -0.33f, 0.33f, textures);
			createProjectile(node, type, +0.33f, 0.33f, textures);
			break;

		case 3:
			createProjectile(node, type, -0.5f, 0.33f, textures);
			createProjectile(node, type,  0.0f, 0.5f, textures);
			createProjectile(node, type, +0.5f, 0.33f, textures);
			break;
	}
}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->getMaxSpeed());

	float sign = isAllied() ? -1.f : +1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
	node.attachChild(std::move(projectile));
}

void Aircraft::createPickup(SceneNode& node, const TextureHolder& textures) const{
	auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Aircraft::updateTexts(){

	// Set aircraft health display text, position and rotation.
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	if(mMissileDisplay){
		if (mMissileAmmo == 0){
			mMissileDisplay->setString("");
		}else{
			mMissileDisplay->setString("M: " + toString(mMissileAmmo));
		}
	}
}


// Textures::ID toTextureID(Aircraft::Type type){
// 	switch(type){
// 		case Aircraft::Eagle:
// 			return Textures::Eagle;
// 		case Aircraft::Raptor:
// 			return Textures::Raptor;
// 	}
// 	return Textures::Eagle;
// }
