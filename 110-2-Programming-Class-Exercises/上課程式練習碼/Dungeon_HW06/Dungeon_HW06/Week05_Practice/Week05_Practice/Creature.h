#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Functions.h"

//************************************************************
// Creature Class
//************************************************************
class Creature {
private:
	Position	sPos;			// Creature position
	std::string sIcon = "C";	// Creature icon
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = "C";
	};
	// Setting constructor
	Creature(int x, int y, std::string icon = "C") {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sIcon = icon;
	};

	// Setting constructor
	Creature(Position& pos, std::string icon = "C") {
		this->sPos = pos;
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

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	std::string getIcon(void) { return this->sIcon; }

public:
	void update(Position hPos) {
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = "!";
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = "C";
		}
	}
};
