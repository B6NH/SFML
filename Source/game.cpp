#include <SFML/Graphics.hpp>
#include "../Header/game.h"
#include "../Header/resource_identifiers.h"

Game::Game() :
  mWindow(sf::VideoMode(640,480), "SFML App"), mWorld(mWindow),
  mPlayer(), TimePerFrame(sf::seconds(1.f/60.f)){
    mWindow.setKeyRepeatEnabled(false);
}

void Game::run(){

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(mWindow.isOpen()){

    processInput();
    timeSinceLastUpdate += clock.restart();

    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);
    }

    render();
  }

}

void Game::processInput(){

  CommandQueue & commands = mWorld.getCommandQueue();

  sf::Event event;

  while(mWindow.pollEvent(event)){
    mPlayer.handleEvent(event,commands);

    if(event.type == sf::Event::Closed){
      mWindow.close();
    }
  }

  mPlayer.handleRealtimeInput(commands);
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
