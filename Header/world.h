#ifndef WORLD__H__
#define WORLD__H__

#include "resource_holder.h"
#include "resource_identifiers.h"
#include "scene_node.h"
#include "sprite_node.h"
#include "aircraft.h"
#include "command_queue.h"
#include "command.h"
#include "pickup.h"
#include "bloom_effect.h"
#include "sound_player.h"
#include "network_protocol.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


namespace sf{
	class RenderTarget;
}

class NetworkNode;

class World : private sf::NonCopyable{
	public:
		World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds, bool networked = false);
		void update(sf::Time dt);
		void draw();
		sf::FloatRect getViewBounds() const;
		CommandQueue & getCommandQueue();
		Aircraft * addAircraft(int identifier);
		void removeAircraft(int identifier);
		void setCurrentBattleFieldPosition(float lineY);
		void setWorldHeight(float height);
		void addEnemy(Aircraft::Type type, float relX, float relY);
		void sortEnemies();
		bool hasAlivePlayer() const;
		bool hasPlayerReachedEnd() const;
		void setWorldScrollCompensation(float compensation);
		Aircraft * getAircraft(int identifier) const;
		sf::FloatRect getBattlefieldBounds() const;
		void createPickup(sf::Vector2f position, Pickup::Type type);
		bool pollGameAction(GameActions::Action& out);

	private:
		void loadTextures();
		void adaptPlayerPosition();
		void adaptPlayerVelocity();
		void handleCollisions();
		void buildScene();
		void addEnemies();
		void spawnEnemies();
		void destroyEntitiesOutsideView();
		void guideMissiles();
		void updateSounds();

	private:
		enum Layer{
			Background,
			LowerAir,
			UpperAir,
			LayerCount
		};

		struct SpawnPoint{
			SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y){
        //
			}

			Aircraft::Type type;
			float x;
			float y;
		};


	private:

		sf::RenderTarget & mTarget;
		sf::RenderTexture mSceneTexture;
		sf::View mWorldView;
		TextureHolder mTextures;
		FontHolder & mFonts;
		SoundPlayer & mSounds;
		SceneNode mSceneGraph;
		std::array<SceneNode*, LayerCount> mSceneLayers;
		CommandQueue mCommandQueue;
		sf::FloatRect mWorldBounds;
		sf::Vector2f mSpawnPosition;
		float mScrollSpeed;
		float mScrollSpeedCompensation;
		std::vector<Aircraft*> mPlayerAircrafts;
		std::vector<SpawnPoint> mEnemySpawnPoints;
		std::vector<Aircraft*> mActiveEnemies;
		BloomEffect mBloomEffect;
		bool mNetworkedWorld;
		NetworkNode * mNetworkNode;
		SpriteNode * mFinishSprite;
};


#endif
