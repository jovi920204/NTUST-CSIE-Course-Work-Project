#pragma once
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class Replay
{
private:
	std::string readPath;
	std::vector<std::string> moveLog;
	int readMoveIndex;
	int gameStatus;	// -1: in game, 0: red win, 1: black win
public:
	Replay() { readPath = ""; readMoveIndex = 0; gameStatus = -1; };

	void selectFile();
	void readFile();

	void reset();
	void setMoveIndex(int index) { readMoveIndex = index; };

	int getStatus() { return gameStatus; };
	std::string getReadPath() { return readPath; };
	std::string getBackMove() { return moveLog.back(); };
	std::string getCurrent() { return moveLog[readMoveIndex]; };
	std::vector<std::string> getMoveLog() { return moveLog; }


	std::string operator++(int);
};

