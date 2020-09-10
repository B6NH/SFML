#ifndef STATE_STACK__H__
#define STATE_STACK__H__

#include "state.h"
#include "state_identifiers.h"
#include "resource_identifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable{
public:
  enum Action{
    Push,
    Pop,
    Clear
  };
public:
  explicit StateStack(State::Context);
  template<typename T>
  void registerState(States::ID);
  void update(sf::Time);
  void draw();
  void handleEvent(const sf::Event &);
  void pushState(States::ID);
  void popState();
  void clearStates();
  bool isEmpty() const;
private:
  State::Ptr createState(States::ID);
  void applyPendingChanges();
private:
  struct PendingChange{
    explicit PendingChange(Action action, States::ID stateID = States::None);
    Action action;
    States::ID stateID;
  };
private:
  std::vector<State::Ptr> mStack;
  std::vector<PendingChange> mPendingList;
  State::Context mContext;
  std::map<States::ID,std::function<State::Ptr()>> mFactories;
};

template <typename T>
void StateStack::registerState(States::ID stateID){
	mFactories[stateID] = [this] (){
		return State::Ptr(new T(*this, mContext));
	};
}

#endif
