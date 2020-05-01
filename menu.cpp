#include "menu.h"

Menu::Menu(){
  buttons.at(0) = Button(600,50);
  buttons.at(1)= Button(600,150);
  buttons.at(2) = Button(600,250);
  buttons.at(0).FocusOn(); focus = 0;
}

void Menu::Key(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    focus--;
    if(focus < 0){ focus = buttons.size()-1; }
    for(auto & button : buttons){ button.FocusOff(); }
    buttons.at(focus).FocusOn();
  }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    focus++;
    if(focus >= buttons.size()){ focus = 0; }
    for(auto & button : buttons){ button.FocusOff(); }
    buttons.at(focus).FocusOn();
  }
}

void Menu::DrawOn(sf::RenderWindow & window){
  for(const auto & button : buttons){
    button.DrawOn(window);
  }
}
