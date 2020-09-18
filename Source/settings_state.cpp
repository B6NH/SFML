#include "../Header/settings_state.h"
#include "../Header/utility.h"
#include "../Header/resource_holder.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack & stack, Context context) :
State(stack, context), mGUIContainer(){

	// Set background texture.
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	// Add button labels
	addButtonLabel(Player::MoveLeft, 100.f, "Move Left", context);
	addButtonLabel(Player::MoveRight,	150.f, "Move Right", context);
	addButtonLabel(Player::MoveUp, 200.f, "Move Up", context);
	addButtonLabel(Player::MoveDown, 250.f, "Move Down", context);
	addButtonLabel(Player::Fire, 300.f, "Fire", context);
	addButtonLabel(Player::LaunchMissile,	350.f, "Missile", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);

	backButton->setPosition(400.f, 300.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw(){
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time){
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event){
	bool isKeyBinding = false;

	// If button is active assign key to action, deactivate and break.
	for (std::size_t action = 0; action < Player::ActionCount; ++action){
		if (mBindingButtons[action]->isActive()){
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased){
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// Update labels if key was active. Otherwise, pass event to GUI container.
	if(isKeyBinding){
    updateLabels();
  }else{
    mGUIContainer.handleEvent(event);
  }

	return false;
}

// Set key names in labels.
void SettingsState::updateLabels(){

	Player & player = *getContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i){
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(toString(key));
	}
}

// Create button for action.
void SettingsState::addButtonLabel(Player::Action action, float y, const std::string & text, Context context){
	mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text);

	// Button must be manually deactivated.
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
