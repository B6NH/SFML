#include "../Header/game_state.h"


// Call base constructor, initialize mWorld and mPlayer with render window and
// player variables from context.
GameState::GameState(StateStack& stack, Context context) :
  State(stack, context), mWorld(*context.window, *context.fonts), mPlayer(*context.player){
    //
}

// Draw whole world
void GameState::draw(){
	mWorld.draw();
}


// Update world and handle player real time input.
bool GameState::update(sf::Time dt){
	mWorld.update(dt);

	CommandQueue & commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}


// Handle player events.
bool GameState::handleEvent(const sf::Event& event){
	CommandQueue & commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

  // Pause game
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
    requestStackPush(States::Pause);
  }

	return true;
}
