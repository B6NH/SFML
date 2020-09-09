#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Header/game.h"

int main(){

  try{
    Game game;
    game.run();
  }catch (std::exception& e){
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    return 1;
  }

}
