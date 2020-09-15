#include "../Header/title_state.h"
#include "../Header/utility.h"
#include "../Header/resource_holder.h"

#include <SFML/Graphics/RenderWindow.hpp>


// State for game title with blinking text
TitleState::TitleState(StateStack& stack, Context context) :
  State(stack, context), mText(), mShowText(true), mTextEffectTime(sf::Time::Zero){
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

  // Get values from context.
	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("Press any key to start");
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

// Draw background and blinking text
void TitleState::draw(){
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

// Update variable to create blinking effect
bool TitleState::update(sf::Time dt){
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f)){
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}


// If any key was pressed pop this state and push menu state
bool TitleState::handleEvent(const sf::Event& event){

  // Add requests to queue
	if (event.type == sf::Event::KeyReleased){
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}
