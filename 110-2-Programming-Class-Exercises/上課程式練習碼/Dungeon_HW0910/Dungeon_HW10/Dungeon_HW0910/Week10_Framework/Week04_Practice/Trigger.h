#pragma once
#include "Item.h"

//************************************************************
// Trigger Class
//************************************************************
class Trigger : public Item
{
private:
	int			sExpAmount;		// Set up the amount gain
public:
	// Default constructor
	Trigger(void) {
		sPos.x = 6;
		sPos.y = 7;
		sExpAmount = 5;
		sIcon = 'T';
	};

	// Setting constructor
	Trigger(int x, int y, int amt, char icon = 'T') {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sExpAmount = amt;
		this->sIcon = icon;
	};

	// Setting constructor
	Trigger(Position& pos, int amt, char icon = 'T') {
		this->sPos = pos;
		this->sExpAmount = amt;
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

	// Set the amount
	void SetAmount(int amt) { this->sExpAmount = amt; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get the amount 
	int getExpAmount(void) { return this->sExpAmount; }

	void trigger(Item* h) {
		h->gainEXP(sExpAmount);
	}
	void TirggerUpdate(Item* h) {
		if (this->sPos.x == h->getPos().x && this->sPos.y == h->getPos().y) {
			this->trigger(h);
		}
		return;
	}
	
};

