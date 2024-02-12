#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "Replay.h"
#include "Button.h"
#include "Board.h"
#include "Network.h"


class Viewer
{
private:
	sf::RenderWindow* window;
	std::time_t start_time;
	std::time_t last_update_time;
	std::time_t now_time;
	int timeLimit = 100;
	int update_interval = 1;

	// main page object
	sf::Texture titleTexture;
	sf::Sprite* title;
	Button startButton, exitButton, loadButton,onlineButton;

	// game page object
	sf::Texture boardTexture;
	sf::Sprite* boardBackground;
	Button surrenderButton;

	// load log object
	Replay replay;
	Button nextStepButton;

	//online game
	Network onlineGame;
public:
	Viewer();
	~Viewer();

	const bool windowIsRunning() const { return window->isOpen(); };
	sf::RenderWindow& getWindow() { return *window; };

	void initMainPage();
	void initGamePage();
	void initReplayPage();
	void initOnlinePage();

	int updateMainPage(sf::Event);
	int updateGamePage(sf::Event, Board*);
	int updateGamePage( Board*);
	int updateReplayPage(sf::Event, Board*);
	int updateOnlinePage(sf::Event, Board*, bool is_from_user);
	int updateOnlinePage(Board*);

	void showMainPage();
	void showGamePage(Board*);
	void showReplayPage(Board*);
	void showOnlinePage(Board*);
};
