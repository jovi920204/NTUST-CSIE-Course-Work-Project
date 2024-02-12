/************************************************************************
File:        Source.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		陳俊宇，JYCReports@gmail.com
Student modifier:
		張睿麟，b11015030@mail.ntust.edu.tw
Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，
		ESC是離開畫面。同時更新圖版上的資訊。

************************************************************************/
#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function

//************************************************************
// The location in the board
//************************************************************
struct Position {
	int x; // X, y Coordinate
	int y;
};

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);
void showDirection(Position, Position);
//************************************************************
// Hero Class, only has requirement part for example
//************************************************************
class Hero {
private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
	int heroAttack = 2;
public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = 'H';
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

	// Incrementally move the elements 
	void move(int x, int y) {
		// Implement Hero controls
		/*Please implement your code here*/
		sPos.x += x;
		sPos.y += y;
		if (!isPositionValid(sPos)) {
			sPos.x -= x;
			sPos.y -= y;
		}

		/************************************************************************/
	}
	int getAttack(void) {
		return this->heroAttack;
	}
};

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position& pos2);

class Creature {

	// Implement Creature Class
	/*Please implement your code here*/
private:
	Position	sPos;			// Hero location
	char sIcon = 'C';	// Creatur icon
	int creatureHP = 10;
	bool creatureCanSee = false;
	bool creatureGetHurt = false;
public:
	// Default constructor
	Creature() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = 'C';
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) {
		this->sIcon = icon; 
	}

	// Get position
	Position getPos(void) { 
		return this->sPos;
	}

	// Get Icon
	char getIcon(void) { 
		return this->sIcon; 
	}
	int getHP(void) {
		return this->creatureHP;
	}
	bool getCreatureCanSee(void){
		return this->creatureCanSee;
	}
	bool getCreatureGetHurt(void) {
		return this->creatureGetHurt;
	}
	void update(class Hero hero) {
		Position dir;
		Position heroPos = hero.getPos();
		if (canSee(sPos, heroPos, dir)) {
			this->creatureCanSee = true;
			sPos.x += dir.x;
			sPos.y += dir.y;
		} 
		else if (sPos.x + dir.x == heroPos.x && sPos.y + dir.y == heroPos.y) {
			this->creatureGetHurt = true;
			this->creatureHP -= hero.getAttack();
		}
		else {
			this->creatureCanSee = false;
			this->creatureGetHurt = false;
			sPos = sPos;
		}
		//std::cout << "dir" << dir.x << ", " << dir.y << std::endl;
	}



	/************************************************************************/

};
// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 10;
const int GHEIGHT = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char gBoard[GHEIGHT][GWIDTH] = {
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GNOTHING,	GNOTHING,	GNOTHING,	GWALL,
	GWALL,		GWALL,		GWALL,		GWALL,		GWALL
};

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	INVALID,
};

Hero gHero;
Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 判斷位置是否為空
bool isPositionValid(Position& loc);
// 初始化版面
void setupBoard();
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

int main(int argc, char** argv)
{
	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[6];

	// Setup a clear dungeon
	setupBoard();

	// Set the position of Hero
	gHero.setPos(2, 2);

	gCreature.setPos(5, 6);

	// Draw the bord and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Get the press key
	keyUpdate(gKeyState);

	// Run the game loop
	while (!gKeyState[ValidInput::EESC] && gCreature.getHP() != 0) {
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

	system("pause");
	return 0;
}

//******************************************************************
//
// * 偵測輸入狀態
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * 判斷位置是否為空
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
// * 利用 call-by-referce 將計算得到的方向回傳
//==================================================================
bool canSee(Position cPos, Position hPos, Position& dir)
//==================================================================
{
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 2;
	do {
		// spot the target position
		if (cPos.x + dir.x * count == hPos.x &&
			cPos.y + dir.y * count == hPos.y ) {
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
	std::cout << "Use wsad key to moved Hero " << gHero.getIcon() << std::endl;
	std::cout << "Pressed ESC key to exit\n\n";
	// Print Outputs
	/*Please implement your code here*/
	std::cout << "Hero's Attack = " << gHero.getAttack() << std::endl;
	std::cout << "Creature's HP = " << gCreature.getHP() << std::endl;
	std::cout << "\nHero is at Creature's ";
	showDirection(gCreature.getPos(), gHero.getPos());
	std::cout << " direction.\n" << std::endl;
	if (gCreature.getCreatureCanSee()) {
		std::cout << "Creature can see Hero." << std::endl;
	}
	if (gCreature.getCreatureGetHurt()) {
		std::cout << "Creature get hurt." << std::endl;
	}

	
	if (gCreature.getHP() == 0) {
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Hero wins!!!" << std::endl;
	}
	/************************************************************************/
}
//******************************************************************
//
// * Show the direction
//==================================================================
void showDirection(Position cPos, Position hPos) {
	int x, y;
	x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	if (x == 0 && y == -1) {
		std::cout << "N";
	}
	if (x == 1 && y == -1) {
		std::cout << "EN";
	}
	if (x == 1 && y == 0) {
		std::cout << "E";
	}
	if (x == 1 && y == 1) {
		std::cout << "ES";
	}
	if (x == 0 && y == 1) {
		std::cout << "S";
	}
	if (x == -1 && y == 1) {
		std::cout << "WS";
	}
	if (x == -1 && y == 0) {
		std::cout << "W";
	}
	if (x == -1 && y == -1) {
		std::cout << "WN";
	}
}
//==================================================================
//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// 清除版面
	system("CLS");

	// 是否有input
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
	else {
		std::cout << "invalid input\n";
	}
	//Calculate and Initiate Move
	gCreature.update(gHero);
	draw();
	drawInfo();
}
