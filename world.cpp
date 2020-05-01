#include "world.h"

void World::DrawOn(sf::RenderWindow & window){
  menu.DrawOn(window);
}

void World::Key(){
  menu.Key();
}
