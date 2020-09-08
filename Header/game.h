#ifndef GAME__H__
#define GAME__H__
#include "player.h"
#include "resource_holder.h"
#include "textures.h"
#include "world.h"

class Game{
public:
  Game();
  void run();
private:
  void processInput();
  void update(sf::Time);
  void render();
private:
  sf::RenderWindow mWindow;
  World mWorld;
  Player mPlayer;
  sf::Time TimePerFrame;
};

#endif
