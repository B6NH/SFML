#ifndef SOUND_NODE__H__
#define SOUND_NODE__H__

#include "scene_node.h"
#include "resource_identifiers.h"


class SoundPlayer;

class SoundNode : public SceneNode{
	public:
		explicit SoundNode(SoundPlayer& player);
		void playSound(SoundEffect::ID sound, sf::Vector2f position);
		virtual unsigned int	getCategory() const;
	private:
		SoundPlayer & mSounds;
};

#endif
