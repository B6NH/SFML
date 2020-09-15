#include "../Header/aircraft.h"
#include "../Header/category.h"
#include "../Header/command_queue.h"
#include "../Header/player.h"
#include <iostream>

struct AircraftMover{
	AircraftMover(float vx, float vy) : velocity(vx, vy){
    //
  }

	void operator() (Aircraft& aircraft, sf::Time) const{
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};


// Initialize player object. Bind keys to Action enums.
// Initialize actions by binding Action enums to commands.
Player::Player(){

	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	initializeActions();

	// Set all commands category to PlayerAircraft
	for(auto & pair : mActionBinding){
    pair.second.category = Category::PlayerAircraft;
  }

}

void Player::handleEvent(const sf::Event & event, CommandQueue & commands){
	if (event.type == sf::Event::KeyPressed){

		// Find key binding
		auto found = mKeyBinding.find(event.key.code);

		// If key binding was found for nonRealtimeAction push command to queue.
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second)){
      commands.push(mActionBinding[found->second]);
    }
	}
}

// Push command for realtimeAction.
void Player::handleRealtimeInput(CommandQueue & commands){
	for(auto pair : mKeyBinding){
		if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second)){
      commands.push(mActionBinding[pair.second]);
    }
	}
}

// Assign key to Action enum
void Player::assignKey(Action action, sf::Keyboard::Key key){
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ){
		if (itr->second == action){
      mKeyBinding.erase(itr++);
    }else{
      ++itr;
    }
	}
	mKeyBinding[key] = action;
}

// Get key for Action enum
sf::Keyboard::Key Player::getAssignedKey(Action action) const{
	for(auto pair : mKeyBinding){
		if (pair.second == action){
      return pair.first;
    }
	}
	return sf::Keyboard::Unknown;
}


void Player::initializeActions(){
	const float playerSpeed = 250.f;

	// Set action functions of type std::function<void(SceneNode&,sf::Time)>.
	// Functions are created with derivedAction template and functional object
	// of type AircraftMover.
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}


bool Player::isRealtimeAction(Action action){
	switch (action){
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;

		default:
			return false;
	}
}
