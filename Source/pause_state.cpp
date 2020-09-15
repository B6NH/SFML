#include "../Header/pause_state.h"
#include "../Header/utility.h"
#include "../Header/resource_holder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context) :
  State(stack, context), mBackgroundSprite(), mPausedText(),
  mInstructionText(){

  // Set font from context and get view size
	sf::Font & font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

  // Set pause message
	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  // Set instruction message
	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}


// Draw pause screen. Game is in background
void PauseState::draw(){
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

  // Partially transparent shape
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

// False value prevents updating other states in stack.
bool PauseState::update(sf::Time){
	return false;
}

bool PauseState::handleEvent(const sf::Event& event){

	if(event.type != sf::Event::KeyPressed){
    return false;
  }

  // Go back to game
	if(event.key.code == sf::Keyboard::Escape){
		requestStackPop();
	}

  // Clear stack and return to menu
	if (event.key.code == sf::Keyboard::BackSpace){
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}
