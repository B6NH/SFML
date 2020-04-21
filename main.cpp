#include <SFML/Graphics.hpp>

// g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

int main()
{

    const float SPEED = 40;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(20);

    sf::RectangleShape square(sf::Vector2f(60, 60));
    square.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                square.move(-SPEED,0);
              }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                square.move(SPEED,0);
              }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                square.move(0,-SPEED);
              }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                square.move(0,SPEED);
              }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
              }
              //square.setFillColor(sf::Color::Red);
            }
        }

        window.clear();
        window.draw(square);
        window.display();
    }

    return 0;
}
