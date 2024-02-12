#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>
#include <string>
#include "Position.h"
class Hero;
class Creature;
class Trigger;

// Constent value
const std::string GWALL = "O";
const std::string GNOTHING = " ";

// Board size
const int GWIDTH = 10;
const int GHEIGHT = 10;

// Destinated game loop period
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

std::string     gBoard[][GWIDTH];
extern Hero		gHero;
extern Creature gCreature;
extern Trigger  gTrigger;

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position& pos2);

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

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 判斷位置是否為空
bool isPositionValid(Position& loc);

// Initial board
void initBoard(void);

// 輸出版面
void draw(void);

// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

#endif //__FUNCTIONS_H__