#ifndef APPLICATION__H__
#define APPLICATION__H__
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "resource_holder.h"
#include "resource_identifiers.h"
#include "player.h"
#include "state_stack.h"
#include "music_player.h"
#include "sound_player.h"


class Application{
public:
  Application();
  void run();
private:
  void processInput();
  void update(sf::Time dt);
  void render();
  void updateStatistics(sf::Time dt);
  void registerStates();

private:
  static const sf::Time	TimePerFrame;
  sf::RenderWindow mWindow;
  TextureHolder mTextures;
  FontHolder mFonts;
  MusicPlayer mMusic;
  SoundPlayer mSounds;
  Player mPlayer;
  StateStack mStateStack;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames;
};

#endif
