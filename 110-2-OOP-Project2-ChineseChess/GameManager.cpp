#include "GameManager.h"

GameManager::GameManager()
{
	flowControl = 0;
	this->ev = sf::Event();
	viewer.initMainPage();
}

GameManager::~GameManager()
{
}

const bool GameManager::isRunning() const
{
	return viewer.windowIsRunning();
}

void GameManager::update()
{
	while (viewer.getWindow().pollEvent(ev))
	{
		int temp = 0;
		switch (flowControl)
		{
		case 0:
			temp = viewer.updateMainPage(ev); break;
		case 1:
			temp = viewer.updateGamePage(ev, &board); break;
		case 2:
			temp = viewer.updateReplayPage(ev, &board); break;
		case 3:
			temp = viewer.updateOnlinePage(ev, &board,true);
			break;
		}
		if (flowControl != temp)
		{
			switch (temp)
			{
			case 0:
				viewer.initMainPage(); break;
			case 1:
				viewer.initGamePage(); break;
			case 2:
				viewer.initReplayPage(); break;
			case 3:
				viewer.initOnlinePage(); 
				break;
			}
			flowControl = temp;
		}
	}


	if (flowControl == 1) {
		int temp = 0;
		temp = viewer.updateGamePage(&board);
		if (flowControl != temp)
		{
			switch (temp)
			{
			case 0:
				viewer.initMainPage(); break;
			}
			flowControl = temp;
		}
	}
	if (flowControl == 3) {
		int temp = 0;
		temp = viewer.updateOnlinePage( &board);
		if (flowControl != temp)
		{
			switch (temp)
			{
			case 0:
				viewer.initMainPage(); break;
			case 1:
				viewer.initGamePage(); break;
			}
			flowControl = temp;
		}
	}
}

void GameManager::render()
{
	switch (flowControl)
	{
	case 0:
		viewer.showMainPage(); break;
	case 1:
		viewer.showGamePage(&board); break;
	case 2:
		viewer.showReplayPage(&board); break;
	case 3:
		viewer.showOnlinePage(&board); break;
	}
}