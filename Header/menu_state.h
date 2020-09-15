#ifndef MENU_STATE__H__
#define MENU_STATE__H__

#include "container.h"
#include "state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State{
	public:
    MenuState(StateStack &, Context);
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	private:
		sf::Sprite mBackgroundSprite;
		GUI::Container mGUIContainer;
};

#endif
