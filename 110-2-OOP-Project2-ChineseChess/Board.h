#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "OutputLog.h"
#include "Chess.h"

struct Point { int x; int y; };
class Board
{
private:
	// Board store the name of chesses
	std::vector<std::vector<std::string> > nameTable;
	// chessBoard store the class of chesses
	std::vector<std::vector<Chess*>> chessBoard;
	// removed chess img path
	std::vector<std::string> removedChesses; 
	Point chosenChessIndex;
	std::string checkmate;
	std::string winner;
	int roundCount;

	// a, b variables for moveChess function
	Chess* chessA, chessB;
public:
	Board();
	~Board();

	OutputLog outputLog;
	std::vector<std::string> getRemovedChesses() { return removedChesses; };
	std::vector<std::vector<Chess*>> getBoard() { return chessBoard; };
	Point getChosenChessIndex() { return chosenChessIndex; };
	std::string getCheckmate() { return checkmate; };
	int getRoundCount() { return roundCount; };
	std::string getWinner() { return winner; };
	void setWinner(std::string win) { winner = win; };

	void addRemovedChess(std::string name) { removedChesses.push_back(name); };
	void setCheckmate(std::string checkmate) { this->checkmate = checkmate; };
	void setChosenChessIndex(Point p) { chosenChessIndex = { p.x,p.y }; };
	void resetBoard();

	Chess* clickBoard(sf::Event&, sf::RenderWindow*);
	void swapChess(Chess*, Chess*);
	void removeChess(Point);
};