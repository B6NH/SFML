#ifndef STATE__H__
#define STATE__H__
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "resource_identifiers.h"
#include "state_identifiers.h"

namespace sf{
	class RenderWindow;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;
class KeyBinding;


// State class represents different game states. It contains pointer to
// state stack and application context with window, resources and player.
class State{
public:
  typedef std::unique_ptr<State> Ptr;
  struct Context{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
			MusicPlayer& music, SoundPlayer& sounds, KeyBinding& keys1, KeyBinding& keys2);
    sf::RenderWindow * window;
    TextureHolder * textures;
    FontHolder * fonts;
		MusicPlayer * music;
		SoundPlayer * sounds;
		KeyBinding * keys1;
		KeyBinding * keys2;
  };
public:
  State(StateStack &, Context);
  virtual ~State();
  virtual void draw() = 0;
  virtual bool update(sf::Time) = 0;
  virtual bool handleEvent(const sf::Event &) = 0;
	virtual void onActivate();
	virtual void onDestroy();
protected:
  void requestStackPush(States::ID);
  void requestStackPop();
  void requestStateClear();
  Context getContext()const;
private:
  StateStack * mStack;
  Context mContext;
};

#endif
