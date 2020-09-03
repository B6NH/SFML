#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Header/game.h"

int main(){

  try{
    Game game;
    game.run();
  }catch (std::runtime_error& e){
    std::cout << "Exception: " << e.what() << std::endl;
    return 1;
  }

}
