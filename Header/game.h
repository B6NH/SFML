#ifndef GAME__H__
#define GAME__H__

class Game{
public:
  Game();
  void run();
  void handlePlayerInput(sf::Keyboard::Key, bool);
private:
  void processEvents();
  void update();
  void render();
private:
  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
  bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
};

#endif
