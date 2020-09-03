#ifndef GAME__H__
#define GAME__H__
#include "resource_holder.h"
#include "textures.h"

class Game{
public:
  Game();
  void run();
  void handlePlayerInput(sf::Keyboard::Key, bool);
private:
  void processEvents();
  void update(sf::Time);
  void render();
private:
  sf::RenderWindow mWindow;
  ResourceHolder<sf::Texture,Textures::ID> mTextures;
  sf::Sprite mPlayer;
  sf::Sprite mLandscape;
  sf::Time TimePerFrame;
  bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
  float PlayerSpeed;
};

#endif
