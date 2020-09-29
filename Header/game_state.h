#ifndef GAME_STATE__H__
#define GAME_STATE__H__
#include "state.h"
#include "world.h"
#include "player.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameState : public State{
  public:
    GameState(StateStack &, Context context);
    virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event & event);
	private:
		World mWorld;
		Player mPlayer;
};

#endif
