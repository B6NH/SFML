#include "button.h"

Button::Button(){}

Button::Button(int x, int y){
  image = sf::RectangleShape(sf::Vector2f(200, 70));
  image.setPosition(x, y);
  image.setFillColor(sf::Color::Green);
}

void Button::DrawOn(sf::RenderWindow & window)const{
  window.draw(image);
}

void Button::FocusOn(){
  image.setFillColor(sf::Color::Red);
}

void Button::FocusOff(){
  image.setFillColor(sf::Color::Green);
}
