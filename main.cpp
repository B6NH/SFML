#include <SFML/Graphics.hpp>
#include "aircraft.h"
#include "entity.h"
#include "rsrc.h"
#include "scenenode.h"

namespace Textures{
  enum ID { Landscape, Airplane, Missile };
}

class Game{
private:
  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
  bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
  float PlayerSpeed;
  sf::Time TimePerFrame;
  void ProcessEvents();
  void Update(sf::Time);
  void Render();
  void HandlePlayerInput(sf::Keyboard::Key, bool);
public:
  Game();
  void Run();
};

int main(){
  ResourceHolder<sf::Texture,Textures::ID> aaa;

  Game game;
  game.Run();
}

Game::Game() : mWindow(sf::VideoMode(640,480), "SFML App"),
               PlayerSpeed(150), mPlayer(),
               TimePerFrame(sf::seconds(1.f / 60.f)){
  mPlayer.setRadius(40.f);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::Run(){

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(mWindow.isOpen()){

    ProcessEvents();

    timeSinceLastUpdate += clock.restart();

    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      ProcessEvents();
      Update(TimePerFrame);
    }

    Render();
  }
}

void Game::ProcessEvents(){
  sf::Event event;
  while(mWindow.pollEvent(event)){
    switch(event.type){
      case sf::Event::KeyPressed:
        HandlePlayerInput(event.key.code,true); break;
      case sf::Event::KeyReleased:
        HandlePlayerInput(event.key.code,false); break;
      case sf::Event::Closed:
        mWindow.close(); break;
    }
  }
}

void Game::Update(sf::Time deltaTime){
  sf::Vector2f mov(0.f,0.f);
  if(mIsMovingUp){ mov.y -= PlayerSpeed; }
  if(mIsMovingDown){ mov.y += PlayerSpeed; }
  if(mIsMovingLeft){ mov.x -= PlayerSpeed; }
  if(mIsMovingRight){ mov.x += PlayerSpeed; }

  mPlayer.move(mov * deltaTime.asSeconds());
}

void Game::Render(){
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}

void Game::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed){
  if(key == sf::Keyboard::W){
    mIsMovingUp = isPressed;
  }else if(key == sf::Keyboard::S){
    mIsMovingDown = isPressed;
  }else if(key == sf::Keyboard::A){
    mIsMovingLeft = isPressed;
  }else if(key == sf::Keyboard::D){
    mIsMovingRight = isPressed;
  }
}
