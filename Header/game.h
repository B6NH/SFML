#ifndef GAME__H__
#define GAME__H__
#include "resource_holder.h"
#include "textures.h"
#include "world.h"

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
  World mWorld;
  sf::Time TimePerFrame;
};

#endif
