//#include "../Header/category.h"
#include "../Header/emitter_node.h"
#include "../Header/projectile.h"
#include "../Header/data_tables.h"
#include "../Header/utility.h"
#include "../Header/resource_holder.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


namespace{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
: Entity(1)
, mType(type)
, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
, mTargetDirection(){
	centerOrigin(mSprite);

	// Add particle system if type is Missile
	if (isGuided()){

		// Add smoke
		std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Smoke));
		smoke->setPosition(0.f, getBoundingRect().height / 2.f);
		attachChild(std::move(smoke));

		// Add propellant
		std::unique_ptr<EmitterNode> propellant(new EmitterNode(Particle::Propellant));
		propellant->setPosition(0.f, getBoundingRect().height / 2.f);
		attachChild(std::move(propellant));

	}

}

// Set unit vector to target
void Projectile::guideTowards(sf::Vector2f position){
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const{
	return mType == Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands){
	if (isGuided()){
		const float approachRate = 200.f;

		// Change velocity with approach rate
		sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}

	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const{
	if (mType == EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const{
	return Table[mType].speed;
}

int Projectile::getDamage() const{
	return Table[mType].damage;
}
