#pragma once
#include <string>
#include "Position.h"
#include "main.h"
class Creature {//creature class 
protected:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
	int damage = 0;				// Creature damage
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = 'C';
	};

	// Set position
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
	int getDamage() { return this->damage; }
	virtual void update(Position hPos) {
		return;
	};
	
};


// Vampire inherited Creature
// move = 1 => 每一次移動一格
// damege = 1
class Vampire : public Creature{
public:	
	Vampire(){
		this->sIcon = 'V';
		damage = 1;
	};
	int getDamage() { return this->damage; }
	void update(Position hPos) {
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Vampire has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
			int randNum = rand() % 4;
			if (randNum == 0)
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


};

// Zombie inherited Creature
// move = 2 => 每兩次移動一格
// damege = 2
class Zombie : public Creature {
private:
	int step;
public:
	Zombie(void) {
		this->sPos.x = 5;
		this->sPos.y = 6;
		this->sIcon = 'Z';
		damage = 2;
		step = 0;
	};
	int getDamage() { return this->damage; }
	void update(Position hPos) {
		step++;
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Zombie has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
			int randNum = rand() % 4;
			if (randNum == 0 && step % 2 == 0)
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
			std::cout << "Zombie didn't find the Hero\n";
			this->sIcon = 'Z';
			int randNum = rand() % 4;
			if (step % 2 == 0) {
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