#include "../Header/application.h"

#include <stdexcept>
#include <iostream>

// g++ -c Source/*.cpp
// g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

int main(){

  try{
    Application app;
		app.run();
  }catch (std::exception& e){
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    return 1;
  }

}
