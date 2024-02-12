#pragma once
#include "Item.h"
class Vampire : public Item
{
private:
	int step = 0;
public:
	Vampire() {
		sPos.x = 5;			// Item position
		sPos.y = 6;
		sIcon = 'V';			// Item icon
		sAttack = 5;		// Item attack
		sHp = 3;			// Item hp
		sLevel = 0;			// Level
		sMaxExp = 0;		// Level update experience
		sCurrentExp = 0;	// current exp hero has
		speed = 1;			// Item speed;
	};
	~Vampire();
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get Attack
	int getAttack() { return this->sAttack; }

	// Get Health
	int getHealth(void) { return this->sHp; }

	void update(Position hPos) {
		step++;
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Vampire has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
			int randNum = rand() % 4;
			if (randNum == 0 && step % speed == 0)
			{
				Position test = sPos;
				test.x += dir.x;
				test.y += dir.y;
				if (isPositionValid(test))
				{
					this->sPos.x += dir.x;
					this->sPos.y += dir.y;
				}
			}
		}
		else {
			std::cout << "Vampire didn't find the Hero\n";
			this->sIcon = 'V';
			int randNum = rand() % 4;
			if (step % speed == 0) {
				if (randNum == 0)
				{
					Position test = sPos;
					test.x += 1;
					if (isPositionValid(test))
					{
						this->sPos.x += 1;
					}
					else
					{
						this->sPos.x -= 1;
					}
				}
				if (randNum == 1)
				{
					Position test = sPos;
					test.x -= 1;
					if (isPositionValid(test))
					{
						this->sPos.x -= 1;
					}
					else
					{
						this->sPos.x += 1;
					}
				}
				if (randNum == 2)
				{
					Position test = sPos;
					test.y += 1;
					if (isPositionValid(test))
					{
						this->sPos.y += 1;
					}
					else
					{
						this->sPos.y -= 1;
					}
				}
				if (randNum == 3)
				{
					Position test = sPos;
					test.y -= 1;
					if (isPositionValid(test))
					{
						this->sPos.y -= 1;
					}
					else
					{
						this->sPos.y += 1;
					}
				}
			}
		}
	}
};
