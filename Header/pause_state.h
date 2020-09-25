#ifndef PAUSE_STATE__H__
#define PAUSE_STATE__H__
#include "state.h"
#include "container.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State{
	public:
    PauseState(StateStack &, Context);
		~PauseState();
		virtual void draw();
		virtual bool update(sf::Time);
		virtual bool handleEvent(const sf::Event &);
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mPausedText;
		GUI::Container mGUIContainer;
};


#endif
