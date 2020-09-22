#include "../Header/emitter_node.h"
#include "../Header/particle_node.h"
#include "../Header/command_queue.h"
#include "../Header/command.h"


EmitterNode::EmitterNode(Particle::Type type)
: SceneNode()
, mAccumulatedTime(sf::Time::Zero)
, mType(type)
, mParticleSystem(nullptr)
{
}

void EmitterNode::updateCurrent(sf::Time dt, CommandQueue& commands){

	// Emit particles if system was initialized
	if (mParticleSystem){
		emitParticles(dt);
	}else{

		// Find particle node with the same type as emitter node
		auto finder = [this] (ParticleNode & container, sf::Time){
			if (container.getParticleType() == mType){
				mParticleSystem = &container;
			}
		};

		// Push command to find particle node
		Command command;
		command.category = Category::ParticleSystem;
		command.action = derivedAction<ParticleNode>(finder);

		commands.push(command);
	}
}

// Emit particles with accumulated time
void EmitterNode::emitParticles(sf::Time dt){
	const float emissionRate = 30.f;
	const sf::Time interval = sf::seconds(1.f) / emissionRate;

	mAccumulatedTime += dt;

	while (mAccumulatedTime > interval){
		mAccumulatedTime -= interval;
		mParticleSystem->addParticle(getWorldPosition());
	}
}
