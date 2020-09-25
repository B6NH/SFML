#include "../Header/game_state.h"
#include "../Header/music_player.h"

#include <SFML/Graphics/RenderWindow.hpp>


// Call base constructor, initialize mWorld and mPlayer with variables from context.
GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player){

	mPlayer.setMissionStatus(Player::MissionRunning);

	context.music->play(Music::MissionTheme);
}

// Draw whole world
void GameState::draw(){
	mWorld.draw();
}


// Update world and handle player real time input.
bool GameState::update(sf::Time dt){
	mWorld.update(dt);

	if(!mWorld.hasAlivePlayer()){
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}else if(mWorld.hasPlayerReachedEnd()){
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
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
