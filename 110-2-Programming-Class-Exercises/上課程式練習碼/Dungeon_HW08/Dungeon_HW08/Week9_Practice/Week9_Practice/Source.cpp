/************************************************************************
File:        main.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		陳俊宇，JYCReports@gmail.com

Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，
		ESC是離開畫面。同時更新圖版上的資訊。

************************************************************************/
#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <string>		// for fullWidth board display
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function

//************************************************************
// The location in the board
//************************************************************
struct Position {
	Position() {
		x = 0;
		y = 0;
	}
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x; // X, y Coordinate
	int y;
};

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);

//************************************************************
// Hero Class, only has requirement part for example
//************************************************************
class Hero {
private:
	Position	sPos;			// Hero location
	std::string sIcon = "Ｈ";	// Hero icon

public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = "Ｈ";
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
};

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position& pos2);

class Creature {//creature class 
private:
	Position	sPos;			// Creature position
	std::string sIcon = "Ｃ";			// Creature icon
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = "Ｃ";
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
			this->sIcon = "C!";
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = "Ｃ";
		}
	}
};

// Constent value
const std::string GWALL = "■";
const std::string GNOTHING = "　";

const int GWIDTH = 11;
const int GHEIGHT = 11;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
std::string** gBoard;

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
// 把版面填滿牆壁
void fillBoard();
// 挖空牆壁
void mazeWalk(std::string** board);
// 遞迴演算法
void mazeStep(std::string** board, Position pos);
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

	// Setup dungeon
	fillBoard();

	// Set the position of Hero
	gHero.setPos(1, 1);

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
// * Fill the board with GWALL
//==================================================================
void fillBoard()
//==================================================================
{
	gBoard = new std::string * [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++) {
		gBoard[i] = new std::string[GWIDTH];
		for (int j = 0; j < GWIDTH; j++) {
			gBoard[i][j] = GWALL;
		}
	}

	mazeWalk(gBoard);
}

//******************************************************************
//
// * pickup start position and start recursion
//==================================================================
void mazeWalk(std::string** board)
//==================================================================
{
	// Implement Determination of start position and make start of recursion
	/*Please implement your code here*/
	Position pos;
	pos.x = 1;
	pos.y = 1;
	srand(time(NULL));
	mazeStep(board, pos);
	/************************************************************************/
}

//******************************************************************
//
// * Recursion part (Be creative)
//==================================================================
void mazeStep(std::string** board, Position pos)
//==================================================================
{
	board[pos.x][pos.y] = GNOTHING;
	bool dir[4] = { 0 }; // 0 上, 1 下, 2 左, 3 右
	int count = 0;
	
	int x = pos.x;
	int y = pos.y;
	Position temp;

	while (count < 4) {
		int dirNum = rand() % 4;
		if (dirNum == 0 && dir[0] == 0) { // 上
			dir[dirNum]++;
			count++;
			if (y - 2 >= 1 && board[x][y - 2] != GNOTHING) {
				board[x][y - 1] = GNOTHING;
				temp.x = x;
				temp.y = y - 2;
				mazeStep(board, temp);
			}
		}
		if (dirNum == 1 && dir[1] == 0) { // 下
			dir[dirNum]++;
			count++;
			if (y + 2 <= GHEIGHT - 2 && board[x][y + 2] != GNOTHING) {
				board[x][y + 1] = GNOTHING;
				temp.x = x;
				temp.y = y + 2;
				mazeStep(board, temp);
			}

		}
		if (dirNum == 2 && dir[2] == 0) { // 左
			dir[dirNum]++;
			count++;
			if (x - 2 >= 1 && board[x-2][y] != GNOTHING) {
				board[x - 1][y] = GNOTHING;
				temp.x = x - 2;
				temp.y = y;
				mazeStep(board, temp);
			}

		}
		if (dirNum == 3 && dir[3] == 0) { // 右
			dir[dirNum]++;
			count++;
			if (x + 2 <= GWIDTH - 2 && board[x + 2][y] != GNOTHING) {
				board[x + 1][y] = GNOTHING;
				temp.x = x + 2;
				temp.y = y;
				mazeStep(board, temp);
			}

		}
	}
	return;
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
	std::string drawBoard[GHEIGHT][GWIDTH];

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	Position c = gCreature.getPos();
	
	while (gBoard[c.y][c.x] != GNOTHING) {
		int dir = rand() % 4;
		if (dir == 1) {
			gCreature.setPos(c.y + 1, c.x);
		}
		else if (dir == 2) {
			gCreature.setPos(c.y - 1, c.x);
		}
		else if (dir == 3) {
			gCreature.setPos(c.y, c.x + 1);
		}
		else if (dir == 4) {
			gCreature.setPos(c.y, c.x - 1);
		}
		c = gCreature.getPos();
	}
	drawBoard[c.y][c.x] = gCreature.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}

	if (h.y == 9 && h.x == 9)
	{
		system("CLS");
		std::cout << "You Win!\n";
		exit(0);
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
	std::cout << "Pressed ESC key to exit\n";
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
	draw();
	drawInfo();
}
