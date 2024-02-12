/************************************************************************
File:        source.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		黃欣云，windyhuang6@gmail.com
		陳俊宇，JYCReports@gmail.com
Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，到T上可以增加經驗
		ESC是離開畫面。同時更新圖版上的資訊。

************************************************************************/

#include "main.h"
#include "Hero.h"
#include "Trigger.h"
#include <vector>
using namespace std;
Hero	 gHero;
Trigger gTrigger1;
Trigger gTrigger2;


class Creature {//creature class 
private:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
public:
	// Default constructor
	Creature(void) {
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

int GWIDTH = -1;
int GHEIGHT = -1;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char **gBoard = NULL;
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

// Create vector of trigger pointer for further managenent and manipulation
/*Please implement your code here*/
vector<Trigger*> gTrigger;




/************************************************************************/



int main(int argc, char** argv)
{
	
	while (GHEIGHT < 5 || GWIDTH < 5)
	{
		std::cout << "Enter Width: ";
		std::cin >> GWIDTH;
		std::cout << "Enter Height: ";
		std::cin >> GHEIGHT;
		system("CLS");
		if (GHEIGHT < 5 || GWIDTH < 5)
		{
			std::cout << "Illegal, both has to be larger than 5.\n";
		}
	}
	// Creation and management of two triggers
	/*Please implement your code here*/
	Trigger *t1 = new Trigger;
	Trigger *t2 = new Trigger;
	gTrigger.push_back(t1);
	gTrigger.push_back(t2);
	/************************************************************************/
	
	srand(time(NULL));
	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[6];

	// Setup a clear dungeon
	setupBoard();

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
	while (!gKeyState[ValidInput::EESC]) {
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
	delete[] gBoard;
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
	// Setup for (random) position of all elements and implementation of game board using 2d dynamic array
	// Elements has to be randomly generated within canvas
	/*Please implement your code here*/
	// setting random  position
	srand((unsigned)time(NULL));
	int xCre = rand() % GWIDTH;
	int yCre = rand() % GHEIGHT;
	while (xCre < 1 || xCre >= GWIDTH - 1 || yCre < 1 || yCre >= GHEIGHT - 1) {
		xCre = rand() % GWIDTH;
		yCre = rand() % GHEIGHT;
	}
	gCreature.setPos(xCre, yCre);
	int xHero = rand() % GWIDTH;
	int yHero = rand() % GHEIGHT;
	while (xHero < 1 || xHero >= GWIDTH - 1 || yHero < 1 || yHero >= GHEIGHT - 1 || (xHero == xCre && yHero == yCre)) {
		xHero = rand() % GWIDTH;
		yHero = rand() % GHEIGHT;
	}
	gHero.setPos(xHero, yHero);
	for (auto val : gTrigger) {
		int x = rand() % GWIDTH;
		int y = rand() % GHEIGHT;
		while (x < 1 || x >= GWIDTH - 1 || y < 1 || y >= GHEIGHT - 1 || (x == xCre && y == yCre) || (x == xHero && y == yHero)) {
			x = rand() % GWIDTH;
			y = rand() % GHEIGHT;
		}
		val->setPos(x, y);
	}

	// initial board
	gBoard = new char* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++) {
		gBoard[i] = new char[GWIDTH];
	}
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
	/************************************************************************/
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	// Setup and implementation of drawing board using 2d vector
	/*Please implement your code here*/
	vector<vector<char>> drawBoard(GHEIGHT,vector<char>(GWIDTH));

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = (gBoard[i][j]);
		}
	}
	/************************************************************************/

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	// Draw two triggers using for loop on drawBoard
	/*Please implement your code here*/
	for (auto val : gTrigger) {
		Position t = val->getPos();
		drawBoard[t.y][t.x] = val->getIcon();
	}
	/************************************************************************/

	if (h.x == c.x && h.y == c.y)
	{
		gHero.damage(1);
	}

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
	std::cout << "The hero is level " << gHero.getLevel() << "\n";
	std::cout << "has " << gHero.getExp() << " EXP" << "\n";
	std::cout << "need " << gHero.getMaxExp() - gHero.getExp() << " to level up\n";
	std::cout << "Hero has " << gHero.getHealth() << " health\n";
	std::cout << "Use arrow key to moved Hero @\n";
	std::cout << "Use Every time you step on a trigger T. the hero gets 10 exp.\n";
	std::cout << "Press ESC key to exit\n";
}

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
	gCreature.update(gHero.getPos());

	// Manipulate update of two triggers using while loop
	/*Please implement your code here*/
	for (auto val : gTrigger) {
		val->update(gHero);
	}
	gCreature.update(gHero.getPos());

	/************************************************************************/

	draw();
	drawInfo();
}
