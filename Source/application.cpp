#include "../Header/application.h"
#include "../Header/utility.h"
#include "../Header/state.h"
#include "../Header/state_identifiers.h"
#include "../Header/title_state.h"
#include "../Header/game_state.h"
#include "../Header/menu_state.h"
#include "../Header/pause_state.h"
#include "../Header/settings_state.h"
#include "../Header/game_over_state.h"


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);


// Application is main game class. It contains game window, resource holders
// with textures and fonts, state stack holding game states, player object and
// statistic variables
Application::Application() :
  mWindow(sf::VideoMode(1024, 768), "Gameplay", sf::Style::Close), mTextures(), mFonts(),
  mPlayer(), mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)),
  mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0){

  // Disable automatic key repeat
	mWindow.setKeyRepeatEnabled(false);
  mWindow.setFramerateLimit(60);

  // Load fonts and textures
	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
  mTextures.load(Textures::ButtonNormal, "Media/Textures/ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected, "Media/Textures/ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed, "Media/Textures/ButtonPressed.png");

  // Set statistic text
	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

  // Register all states with map and factory functions. Stack contains map of
  // type std::map<States::ID,std::function<State::Ptr()>>. Its functions create
  // different states when called.
	registerStates();

  // Push pending change to pending list vector.
	mStateStack.pushState(States::Title);
}

void Application::run(){

  // Start application. Set clock and run main game loop.
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()){

		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

    // Stop updating when time is greater than TimePerFrame
		while (timeSinceLastUpdate > TimePerFrame){
			timeSinceLastUpdate -= TimePerFrame;

      // Process input and update.
			processInput();
			update(TimePerFrame);

			if (mStateStack.isEmpty()){
        mWindow.close();
      }

		}

    // Update statistics and render everything
		updateStatistics(dt);
		render();
	}
}

void Application::processInput(){
	sf::Event event;

  // Handle events with state stack
	while (mWindow.pollEvent(event)){

    // Handle events for every element starting from top of stack. Stop handling
    // events if method returns false value.
		mStateStack.handleEvent(event);

    // Close application window
		if (event.type == sf::Event::Closed){
      mWindow.close();
    }

	}
}


// Update state stack
void Application::update(sf::Time dt){
	mStateStack.update(dt);
}


// Render stack
void Application::render(){
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}


// Update statistics
void Application::updateStatistics(sf::Time dt){
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f)){
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

// All states are registered in mFactories map of mStateStack
// Method registerState creates different factory methods with lambda
void Application::registerStates(){
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
  mStateStack.registerState<SettingsState>(States::Settings);
  mStateStack.registerState<GameOverState>(States::GameOver);
}
