#pragma once
#include <string>
#include "main.h"
class Item
{
protected:
	Position	sPos;			// Item position
	char		sIcon;			// Item icon
	int			sAttack;		// Item attack
	int			sHp;			// Item hp
	int			sLevel;			// Level
	int			sMaxExp;		// Level update experience
	int			sCurrentExp;	// current exp hero has
	int			speed;			// Item speed;
public:
	// Default constructor
	Item(void) {};
	~Item() {};

	// Set position
	virtual void setPos(Position pos) { this->sPos = pos; }
	virtual void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	virtual void setIcon(char icon) { this->sIcon = icon; }

	// Get position
	virtual Position getPos(void) { return this->sPos; }

	// Get Icon
	virtual char getIcon(void) { return this->sIcon; }

	// Get Attack
	virtual int getAttack() { return this->sAttack; }

	// Set level
	virtual void setLevel(int level) { this->sLevel = level; }

	// Set exp
	virtual void setExp(int exp) { this->sCurrentExp = exp; }

	// Set MaxExp
	virtual void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Get level
	virtual int getLevel(void) { return this->sLevel; }

	// Get Exp
	virtual int getExp(void) { return this->sCurrentExp; }

	// Get Max
	virtual int getMaxExp(void) { return this->sMaxExp; }

	// Get Health
	virtual int getHealth(void) { return this->sHp; }

	// Incrementally move the elements 
	virtual void move(int x, int y) {
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
	virtual void gainEXP(int points) {
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

	// Get damage, decrease its HP
	virtual void damage(int points) { this->sHp -= points; }

	virtual void update(Position hPos) { return; }

	virtual void trigger(Item& h) { return; }

	virtual int getExpAmount(void) { return 1; }

	virtual void TirggerUpdate(Item* h) { return; }
};

