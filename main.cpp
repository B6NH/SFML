#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "menu.h"
#include "world.h"

// g++ -c *.cpp && g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

int main()
{

    sf::RenderWindow window(sf::VideoMode(200, 200), "Test");

    window.setFramerateLimit(20);

    World world;

    while(window.isOpen()){

      sf::Event event;

      while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
          window.close();
        }else if(event.type == sf::Event::KeyPressed){
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
          }else{
            world.Key();
          }
        }
      }

      window.clear();
      world.DrawOn(window);
      window.display();

    }

    return 0;
}
