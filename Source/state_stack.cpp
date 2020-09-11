#include <cassert>
#include "../Header/state.h"
#include "../Header/state_stack.h"

StateStack::StateStack(State::Context context) :
  mStack(), mPendingList(), mContext(context), mFactories(){
    //
}

// Update states starting from end of vector
void StateStack::update(sf::Time dt){
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
		if (!(*itr)->update(dt)){
      break;
    }
	}
	applyPendingChanges();
}

// Draw states from oldest to newest
void StateStack::draw(){
	for(State::Ptr& state : mStack){
    state->draw();
  }
}

// Stop handling event if response is false
void StateStack::handleEvent(const sf::Event& event){
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
		if (!(*itr)->handleEvent(event)){
      break;
    }
	}
	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID){
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState(){
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates(){
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const{
	return mStack.empty();
}

// Create state based on stateID
State::Ptr StateStack::createState(States::ID stateID){
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

  // Create state by calling factory function
	return found->second();
}


// Apply pending changes (Push, Pop, Clear)
void StateStack::applyPendingChanges(){
	for(PendingChange change : mPendingList){
		switch (change.action){
			case Push:
				mStack.push_back(createState(change.stateID));
				break;

			case Pop:
				mStack.pop_back();
				break;

			case Clear:
				mStack.clear();
				break;
		}
	}

	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
  action(action), stateID(stateID){
    //
}
