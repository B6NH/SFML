#ifndef GAME__H__
#define GAME__H__

class Game{
public:
  Game();
  void run();
  void handlePlayerInput(sf::Keyboard::Key, bool);
private:
  void processEvents();
  void update(sf::Time);
  void render();
private:
  sf::RenderWindow mWindow;

  sf::Texture mTexture;
  sf::Sprite mPlayer;

  sf::Time TimePerFrame;
  bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
  float PlayerSpeed;
};

#endif
