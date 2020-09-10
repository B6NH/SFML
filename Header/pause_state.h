#ifndef PAUSE_STATE__H__
#define PAUSE_STATE__H__
#include "state.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State{
	public:
    PauseState(StateStack &, Context);
		virtual void draw();
		virtual bool update(sf::Time);
		virtual bool handleEvent(const sf::Event &);
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mPausedText;
		sf::Text mInstructionText;
};


#endif
