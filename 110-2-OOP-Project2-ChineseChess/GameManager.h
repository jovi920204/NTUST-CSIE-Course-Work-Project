#pragma once
#include "Viewer.h"
#include "Board.h"

class GameManager
{
private:
	int flowControl;
	sf::Event ev;
	Board board;
	Viewer viewer;
public:
	GameManager();
	~GameManager();

	const bool isRunning() const;
	void update();
	void render();
};

/*
紅棋：
帥 General
仕 Advisor
相 Elephant
傌 Horse
俥 Chariot
炮 Cannon
兵 Soldier


黑棋：
將 General
士 Advisor
象 Elephant
馬 Horse
車 Chariot
砲 Cannon
卒 Soldier
*/