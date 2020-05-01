#ifndef BUTTON__H__
#define BUTTON__H__

#include <SFML/Graphics.hpp>

class Button{
private:
  sf::RectangleShape image;
  bool focus;
public:
  Button();
  Button(int x, int y);
  void DrawOn(sf::RenderWindow & window)const;
  void FocusOn();
  void FocusOff();
};

#endif
