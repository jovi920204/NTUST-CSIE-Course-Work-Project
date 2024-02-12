/************************************************************************
File:        main.cpp

Author:
		���s�Aea5878158@gmail.com
Modifier:
		�௧�N�Acheeryuchi@gmail.com
		���Y���Awindyhuang6@gmail.com
		���T�t�AJYCReports@gmail.com
Comment:
		�򥻿�J��V���ʥ\��Aw s a d ���ʸ}��W�U���k�A�ťէ��ܸ}�⯸�ߤ��a�O�r���A��T�W�i�H�W�[�g��
		ESC�O���}�e���C�P�ɧ�s�Ϫ��W����T�C

************************************************************************/

#include "main.h"
#include "Hero.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
Hero	 gHero(2, 2);



class Creature {//creature class 
private:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
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
	void setIcon(char& icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

public:
	void update(Position hPos) {
		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = 'C';
		}
	}
};

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 10;
const int GHEIGHT = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// Parameters
int cnt = 0;

// �Ψ��x�s�������
char gBoard[GHEIGHT][GWIDTH] = {
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL
};

// �w�q���ؿ�J���O�P�����}�Cindex
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	MOVEorJUMP = 6,
	ENTER = 7,
	INVALID,
};


Creature gCreature;

// function declare
// ������J���A
void keyUpdate(bool key[]);
// �P�_��m�O�_����
bool isPositionValid(Position& loc);
// ��l�ƪ���
void setupBoard();
// ��X����
void draw(void);
// ��X������T
void drawInfo(void);

// �{���D�X�ʨ禡
void update(bool key[]);
Trigger  gTrigger(5, 5, 10);
int main(int argc, char** argv)
{
	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[7];

	// Setup a clear dungeon
	setupBoard();



	gCreature.setPos(5, 6);

	// Draw the bord and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Get the press key
	//std::cout << "Press Enter to start" << std::endl;
	//keyUpdate(gKeyState);
	//std::cout << "Start of Game! (Press Enter)" << std::endl;

	// Run the game loop
	do {
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	}
	while (!gKeyState[ValidInput::EESC]);

	system("pause");
	return 0;
}

//******************************************************************
//
// * ������J���A
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	// Code Implementation of problem description
	/***************************************************************************************/
	//*****Hint: Modifies needs to be made to the whole function, including the given code below*****//
	/***************************************************************************************/
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	/*Please implement your code here*/
	std::string input;
	std::cin >> input;
	std::size_t found = input.find("Move");
	if (found != std::string::npos) {
		key[ValidInput::MOVEorJUMP] = true;
		char trash;
		int x, y;
		std::cin >> trash >> x >> trash >> y >> trash;
		if (abs(gHero.getPos().x - x) <= 1 && abs(gHero.getPos().y - y) <= 1) {
			gHero.setPos(x, y);
		}
		else {
			key[ValidInput::MOVEorJUMP] = false;
		}
	}
	found = input.find("Jump");
	if (found != std::string::npos) {
		key[ValidInput::MOVEorJUMP] = true;
		char trash;
		int x, y;
		std::cin >> trash >> x >> trash >> y >> trash;
		if (x < 1 || y < 1) {
			key[ValidInput::MOVEorJUMP] = false;
		}
		else {
			gHero.setPos(x, y);
		}
	}
	if (input[input.size() - 1] == 'w') {
		key[ValidInput::EW] = true;
	}
	else if (input[input.size() - 1] == 's') {
		key[ValidInput::ES] = true;
	}
	else if (input[input.size() - 1] == 'a') {
		key[ValidInput::EA] = true;
	}
	else if (input[input.size() - 1] == 'd') {
		key[ValidInput::ED] = true;
	}
	else if (input[input.size() - 1] == ' ') {
		key[ValidInput::ESPACE] = true;
	}
	else if (input[input.size() - 1] == 27) {
		key[ValidInput::EESC] = true;
	}
	

	/************************************************************************/
	
}

//******************************************************************
//
// * �P�_��m�O�_����
//==================================================================
bool isPositionValid(Position& pos)
//==================================================================
{
	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] == GNOTHING) {
		return true;
	}
	return false;
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimun, float maximum)
//==================================================================
{
	return std::max(minimun, std::min(n, maximum));
}

//******************************************************************
//
// * �Q�� call-by-referce �N�p��o�쪺��V�^��
//==================================================================
bool canSee(Position cPos, Position hPos, Position& dir)
//==================================================================
{
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 0;
	do {
		// spot the target position
		if (cPos.x + dir.x * count == hPos.x &&
			cPos.y + dir.y * count == hPos.y) {
			return true;
		}
		count++;
	} while (count < gDistance); // check the range in 4 units
	return false;
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard()
//==================================================================
{
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1) {
				gBoard[i][j] = GWALL;
			}
			else if (j == 0 || j == GWIDTH - 1) {
				gBoard[i][j] = GWALL;
			}
			else {
				gBoard[i][j] = GNOTHING;
			}
		}
	}
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	char drawBoard[GHEIGHT][GWIDTH];

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	Position t = gTrigger.getPos();
	drawBoard[t.y][t.x] = gTrigger.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
	Position hPos = gHero.getPos();
	std::cout << "The hero is level " << gHero.getLevel() << "\n";
	std::cout << "has " << gHero.getExp() << " EXP" << "\n";
	std::cout << "need " << gHero.getMaxExp() - gHero.getExp() << " to level up\n";
	std::cout << "Use arrow key to moved Hero @\n";
	std::cout << "Use Every time you step on a trigger T. the hero get " << gTrigger.getExpAmount() << "EXP point\n";
	std::cout << "Hero is at (" << hPos.x << "," << hPos.y << ")\n";
	std::cout << "Press ESC at end of line to exit\n";
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// �M������
	system("CLS");

	// �O�_��input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		gHero.move(0, -1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		gHero.move(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		gHero.move(-1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		gHero.move(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::MOVEorJUMP]) {
		hasInput = true;
	}
	else {
		std::cout << "invalid input\n";
	}
	gTrigger.update(gHero);
	gCreature.update(gHero.getPos());
	draw();
	drawInfo();
}
