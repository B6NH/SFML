#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include "../Header/sprite_node.h"
#include "../Header/world.h"
#include "../Header/projectile.h"
#include "../Header/pickup.h"
#include "../Header/text_node.h"
#include "../Header/particle_node.h"
#include <SFML/Graphics/RenderWindow.hpp>

// Initialize world object.
World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mFonts(fonts)
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
, mEnemySpawnPoints()
, mActiveEnemies(){

	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

// Load textures for game objects and background
void World::loadTextures(){
	mTextures.load(Textures::Entities, "Media/Textures/Entities.png");
	mTextures.load(Textures::Jungle, "Media/Textures/Jungle.png");
	mTextures.load(Textures::Explosion, "Media/Textures/Explosion.png");
	mTextures.load(Textures::Particle, "Media/Textures/Particle.png");
	mTextures.load(Textures::FinishLine, "Media/Textures/FinishLine.png");
}

// Build game scene
void World::buildScene(){

	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i){

		Category::Type category = (i == LowerAir) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& jungleTexture = mTextures.get(Textures::Jungle);
	jungleTexture.setRepeated(true);

	float viewHeight = mWorldView.getSize().y;
	sf::IntRect textureRect(mWorldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> jungleSprite(new SpriteNode(jungleTexture, textureRect));
	jungleSprite->setPosition(mWorldBounds.left, mWorldBounds.top - viewHeight);
	mSceneLayers[Background]->attachChild(std::move(jungleSprite));

	// Add the finish line to the scene
	sf::Texture& finishTexture = mTextures.get(Textures::FinishLine);
	std::unique_ptr<SpriteNode> finishSprite(new SpriteNode(finishTexture));
	finishSprite->setPosition(0.f, -76.f);
	mSceneLayers[Background]->attachChild(std::move(finishSprite));

	// Add particle node to the scene
	std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Smoke, mTextures));
	mSceneLayers[LowerAir]->attachChild(std::move(smokeNode));

	// Add propellant particle node to the scene
	std::unique_ptr<ParticleNode> propellantNode(new ParticleNode(Particle::Propellant, mTextures));
	mSceneLayers[LowerAir]->attachChild(std::move(propellantNode));

	// Add player's aircraft
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mTextures, mFonts));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mSceneLayers[UpperAir]->attachChild(std::move(player));

	// Add enemy aircraft
	addEnemies();
}


// Add enemies to spawn vector
void World::addEnemies(){

	addEnemy(Aircraft::Raptor,    0.f,  500.f);
	addEnemy(Aircraft::Raptor,    0.f, 1000.f);
	addEnemy(Aircraft::Raptor, +100.f, 1100.f);
	addEnemy(Aircraft::Raptor, -100.f, 1100.f);
	addEnemy(Aircraft::Avenger, -70.f, 1400.f);
	addEnemy(Aircraft::Avenger, -70.f, 1600.f);
	addEnemy(Aircraft::Avenger,  70.f, 1400.f);
	addEnemy(Aircraft::Avenger,  70.f, 1600.f);

  // Sort spawn points in vector. Back of vector is at the bottom.
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs){
		return lhs.y < rhs.y;
	});
}

// Add enemy to list of spawn points
void World::addEnemy(Aircraft::Type type, float relX, float relY){
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

// Create enemies if possible
void World::spawnEnemies(){

  // Create enemies from spawn points in right positions
	while (!mEnemySpawnPoints.empty()
		&& mEnemySpawnPoints.back().y > getBattlefieldBounds().top){
		SpawnPoint spawn = mEnemySpawnPoints.back();

    // Create enemy aircraft
		std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

    // Add enemy aircraft to Air layer
		mSceneLayers[UpperAir]->attachChild(std::move(enemy));

    // Delete spawn point
		mEnemySpawnPoints.pop_back();
	}
}

void World::destroyEntitiesOutsideView(){
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this] (Entity& e, sf::Time){
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			e.destroy();
	});

	mCommandQueue.push(command);
}

// Draw world scene graph
void World::draw(){
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt){

  // Move world view
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	mPlayerAircraft->setVelocity(0.f, 0.f);

	destroyEntitiesOutsideView();
	guideMissiles();

  // Push all commands through scene graph
	while (!mCommandQueue.isEmpty()){
    mSceneGraph.onCommand(mCommandQueue.pop(), dt);
  }

  // Adapt velocity for diagonal movement
	adaptPlayerVelocity();

	handleCollisions();

	mSceneGraph.removeWrecks();
	spawnEnemies();

  // Update scene graph
	mSceneGraph.update(dt, mCommandQueue);

  // Dont let player move outside view bounds
	adaptPlayerPosition();
}

CommandQueue & World::getCommandQueue(){
  return mCommandQueue;
}


void World::adaptPlayerPosition(){
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity(){
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if(velocity.x != 0.f && velocity.y != 0.f){
    mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
  }

	mPlayerAircraft->accelerate(0.f, mScrollSpeed);

}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2){
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2){
		return true;
	}else if (type1 & category2 && type2 & category1){
		std::swap(colliders.first, colliders.second);
		return true;
	}else{
		return false;
	}
}

void World::handleCollisions(){

	// Find collision pairs with std::minmax
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	// Handle all collisions. Swap pairs with matchesCategories if necessary.
	for(SceneNode::Pair pair : collisionPairs){

		if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft)){

			// Player Enemy collision
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);
			player.damage(enemy.getHitpoints());
			enemy.destroy();

		}else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup)){

			// Player Pickup collision
      auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);
			pickup.apply(player);
			pickup.destroy();

		}else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			  || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile)){

			// Aircraft Projectile collision
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			// Apply projectile damage to aircraft, destroy projectile
			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}

void World::guideMissiles(){
	// Setup command that stores all enemies in mActiveEnemies
	Command enemyCollector;
	enemyCollector.category = Category::EnemyAircraft;
	enemyCollector.action = derivedAction<Aircraft>([this] (Aircraft& enemy, sf::Time){
		if (!enemy.isDestroyed()){
      mActiveEnemies.push_back(&enemy);
    }

	});

	// Setup command that guides all missiles to the enemy which is currently closest to the player
	Command missileGuider;
	missileGuider.category = Category::AlliedProjectile;
	missileGuider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time){

		// Ignore unguided bullets
		if(!missile.isGuided()){
      return;
    }

		float minDistance = std::numeric_limits<float>::max();
		Aircraft* closestEnemy = nullptr;

		// Find closest enemy
		for(Aircraft* enemy : mActiveEnemies){
			float enemyDistance = distance(missile, *enemy);

			if (enemyDistance < minDistance){
				closestEnemy = enemy;
				minDistance = enemyDistance;
			}
		}

		if (closestEnemy){
      missile.guideTowards(closestEnemy->getWorldPosition());
    }

	});

	// Push commands, reset active enemies
	mCommandQueue.push(enemyCollector);
	mCommandQueue.push(missileGuider);
	mActiveEnemies.clear();
}

sf::FloatRect World::getViewBounds() const{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const{

	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

bool World::hasAlivePlayer() const{
	return !mPlayerAircraft->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const{
	return !mWorldBounds.contains(mPlayerAircraft->getPosition());
}
