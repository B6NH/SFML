#ifndef MENU__H__
#define MENU__H__

#include <array>
#include "button.h"
#include <SFML/Graphics.hpp>


class Menu{
private:
  std::array<Button,3> buttons;
  int focus;
public:
  Menu();
  void Key();
  void DrawOn(sf::RenderWindow & window);
};


#endif
