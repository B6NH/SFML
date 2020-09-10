#ifndef TITLE_STATE__H__
#define TITLE_STATE__H__

#include "state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State{
	public:
    TitleState(StateStack &, Context);
		virtual void draw();
		virtual bool update(sf::Time);
		virtual bool handleEvent(const sf::Event &);
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mText;
		bool mShowText;
		sf::Time mTextEffectTime;
};

#endif
