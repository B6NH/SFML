#include <SFML/Graphics.hpp>
#include "../Header/game.h"
#include "../Header/textures.h"

Game::Game() :
  mWindow(sf::VideoMode(640,480), "SFML App"), mWorld(mWindow),
  TimePerFrame(sf::seconds(1.f/60.f)){
    //
}

void Game::run(){

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(mWindow.isOpen()){

    processEvents();
    timeSinceLastUpdate += clock.restart();

    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
      update(TimePerFrame);
    }

    render();
  }
}

void Game::processEvents(){
  sf::Event event;
  while(mWindow.pollEvent(event)){

    switch(event.type){
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code,true); break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code,false); break;
      case sf::Event::Closed:
        mWindow.close(); break;
    }

  }
}

void Game::update(sf::Time deltaTime){
  mWorld.update(deltaTime);
}

void Game::render(){
  mWindow.clear();
  mWorld.draw();
  mWindow.setView(mWindow.getDefaultView());
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
  // if(key == sf::Keyboard::W){
  //   mIsMovingUp = isPressed;
  // }else if(key == sf::Keyboard::S){
  //   mIsMovingDown = isPressed;
  // }else if(key == sf::Keyboard::A){
  //   mIsMovingLeft = isPressed;
  // }else if(key == sf::Keyboard::D){
  //   mIsMovingRight = isPressed;
  // }
}
