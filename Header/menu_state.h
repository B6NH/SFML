#ifndef MENU_STATE__H__
#define MENU_STATE__H__

#include "state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State{
	public:
    MenuState(StateStack &, Context);
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
		void updateOptionText();
	private:
		enum OptionNames{
			Play,
			Exit,
		};
	private:
		sf::Sprite mBackgroundSprite;
		std::vector<sf::Text>	mOptions;
		std::size_t mOptionIndex;
};

#endif
