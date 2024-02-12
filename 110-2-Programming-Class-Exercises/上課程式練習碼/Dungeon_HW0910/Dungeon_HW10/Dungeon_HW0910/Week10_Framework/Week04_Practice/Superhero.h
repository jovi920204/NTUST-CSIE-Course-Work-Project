#pragma once
#include "Item.h"
class Superhero : public Item
{
public:
	Superhero() {
		sPos.x = 1;			// Item position
		sPos.y = 1;
		sIcon = 'S';			// Item icon
		sAttack = 0;		// Item attack
		sHp = 20;			// Item hp
		sLevel = 1;			// Level
		sMaxExp = 10;		// Level update experience
		sCurrentExp = 0;	// current exp hero has
		speed = 0;			// Item speed;
	};
	Superhero(int x, int y) {
		sPos.x = x;			// Item position
		sPos.y = y;
		sIcon = 'S';			// Item icon
		sAttack = 0;		// Item attack
		sHp = 20;			// Item hp
		sLevel = 1;			// Level
		sMaxExp = 10;		// Level update experience
		sCurrentExp = 0;	// current exp hero has
		speed = 0;			// Item speed;
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
	void setExp(int exp) { this->sCurrentExp = exp; }

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

	// Get Health
	int getHealth(void) { return this->sHp; }

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

	// Calculate Gain of EXP
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

	void damage(int points) { this->sHp -= points; }

};

