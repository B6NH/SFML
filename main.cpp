#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

// g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app


class Button{
private:
  sf::RectangleShape image;
  bool focus;
public:
  Button(){}
  Button(int x, int y){
    image = sf::RectangleShape(sf::Vector2f(200, 70));
    image.setPosition(x, y);
    image.setFillColor(sf::Color::Green);
  }

  void DrawOn(sf::RenderWindow & window)const{
    window.draw(image);
  }

  void FocusOn(){
    image.setFillColor(sf::Color::Red);
  }

  void FocusOff(){
    image.setFillColor(sf::Color::Green);
  }
};

class Menu{
private:
  std::array<Button,3> buttons;
  int focus;
public:
  Menu(){
    buttons.at(0) = Button(600,50);
    buttons.at(1)= Button(600,150);
    buttons.at(2) = Button(600,250);
    buttons.at(0).FocusOn(); focus = 0;
  }

  void Key(){
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

  void DrawOn(sf::RenderWindow & window){
    for(const auto & button : buttons){
      button.DrawOn(window);
    }
  }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(200, 200), "Test");
    window.setFramerateLimit(20);

    Menu menu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
              }else{
                menu.Key();
              }
            }
        }

        window.clear();
        menu.DrawOn(window);
        window.display();
    }

    return 0;
}
