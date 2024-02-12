#pragma once
#include <string>
#include "Position.h"
#include "main.h"
using namespace std;
//************************************************************
// Hero Class, only has requirement part for example
//************************************************************

class Hero {

private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
	int			sLevel = 1;     // Levelerience
	int			sMaxExp;		// Level update exp
	int			sCurrentExp;	// current exp hero has
	int			HP = 100;
public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 5;
		this->sMaxExp = 10;
		this->sIcon = 'H';
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H') {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H') {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Set level
	void setLevel(int level) { this->sLevel = level; }

	// Set exp
	void setExp(int exp) { 
		cout << "set EXP " << endl;
		this->sCurrentExp = exp; }

	// Set MaxExp
	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get level
	int getLevel(void) { return this->sLevel; }

	// Get Exp
	int getExp(void) { return this->sCurrentExp; }

	// Get Max
	int getMaxExp(void) { return this->sMaxExp; }

	// Incrementally move the elements 
	void move(int x, int y) {
		// Compute the next position
		Position next;
		next.x = this->sPos.x + x;
		next.y = this->sPos.y + y;
		if (isPositionValid(next))
			this->sPos = next;
		else {
			std::cout << "Invalid location\n";
		}
	}
	int getHP() {
		return this->HP;
	}
	// Calculate Gain of EXP
	void gainEXP(int points) {
		// Implement Gain of EXP
		/*Please implement your code here*/
		this->sCurrentExp += points;
		if (this->sCurrentExp >= this->sMaxExp) {
			this->sLevel += (this->sCurrentExp / this->sMaxExp);
			this->sCurrentExp -= this->sMaxExp * (this->sCurrentExp / this->sMaxExp);
		}
		/************************************************************************/
	}
	void damage(int points) {
		// Implement Damage done to Hero
		/*Please implement your code here*/
		HP -= points;




		/************************************************************************/
	}
};
