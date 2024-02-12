#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Hero.h"
#include "main.h"
using namespace std;
//************************************************************
// Trigger Class
//************************************************************
class Trigger {
private:
	Position sPos;
	char sIcon = 'T';
	int sExp;
public:
	Trigger() {
		sPos.x = 1;
		sPos.y = 1;
		sExp = 5;
	}
	Trigger(int _x, int _y, int _exp) {
		sPos.x = _x;
		sPos.y = _y;
		sExp = _exp;
	}
	~Trigger() {};
	Position getPos() {
		return this->sPos;
	}
	char getIcon() {
		return this->sIcon;
	}
	int getExpAmount() {
		return this->sExp;
	}
	void update(Hero& gHero) {
		if (gHero.getPos().x == this->sPos.x && gHero.getPos().y == this->sPos.y) {
			this->sIcon = 'H';
			gHero.gainEXP(this->sExp);
		}
		else {
			this->sIcon = 'T';
		}
	}



	/************************************************************************/
};

