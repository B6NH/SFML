#ifndef PLAYER__H__
#define PLAYER__H__
#include <map>
#include <SFML/Window/Event.hpp>
#include "command.h"

class CommandQueue;

class Player{

public:
  enum Action
  {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    ActionCount
  };

public:
  Player();
  void handleEvent(const sf::Event &, CommandQueue &);
  void handleRealtimeInput(CommandQueue &);
  void assignKey(Action, sf::Keyboard::Key);
  sf::Keyboard::Key getAssignedKey(Action) const;

private:
  std::map<sf::Keyboard::Key, Action> mKeyBinding;
  std::map<Action, Command> mActionBinding;

private:
  void initializeActions();
  static bool isRealtimeAction(Action);
};

#endif
