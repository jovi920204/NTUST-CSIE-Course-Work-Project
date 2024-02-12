#pragma once
#include <string>
#include "Position.h"
#include "Functions.h"

//************************************************************
// Hero Class, only has requirement part for example
//************************************************************
class Hero {

private:
	std::string sIcon = "H";	// Hero icon
	int			sLevel = 1;     // Level
	int			sMaxExp;		// Level update experience
	int			sCurrentExp;	// current exp hero has

public:
	//Position of Hero
	Position sPos;

	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 10;
		this->sIcon = "H";
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 10, int currentExp = 0, std::string icon = "H") {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 10, int currentExp = 0, std::string icon = "H") {
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
	void setIcon(std::string& icon) { this->sIcon = icon; }

	// Set level
	void setLevel(int level) { this->sLevel = level; }

	// Set exp
	void setExp(int exp) { this->sCurrentExp = exp; }

	// Set MaxExp
	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	std::string getIcon(void) { return this->sIcon; }

	// Get level
	int getLevel(void) { return this->sLevel; }

	// Get Exp
	int getExp(void) { return this->sCurrentExp; }

	// Get Max
	int getMaxExp(void) { return this->sMaxExp; }

	// 計算主角獲得的等級與經驗值
	void gainEXP(int points) {
		int number = points;
		while (number > 0) {
			if (sCurrentExp + number >= sMaxExp) {//level up
				number -= (sMaxExp - sCurrentExp);
				sCurrentExp = 0;
				sMaxExp = (int)((float)sMaxExp * 1.2f);
				sLevel++;
			}
			else {
				sCurrentExp += number;
				number = 0;
			}
		}
	}
	void move(char op, int steps)
	{
		// Implementation of movement in Hero Class
		/*Please implement your code here*/
		if (op == '*') {
			if (sPos.x - 1 >= 1) {
				sPos.x -= 1;
			}
			
		}
		else if (op == '/') {
			if (sPos.x + 1 < 9) {
				sPos.x += 1;
			}
			
		}




		/************************************************************************/
		;
	}
	
};