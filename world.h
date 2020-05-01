#ifndef WORLD__H__
#define WORLD__H__

#include <SFML/Graphics.hpp>
#include "menu.h"

class World{
private:
  Menu menu;
public:
  void DrawOn(sf::RenderWindow & window);
  void Key();
};

#endif
