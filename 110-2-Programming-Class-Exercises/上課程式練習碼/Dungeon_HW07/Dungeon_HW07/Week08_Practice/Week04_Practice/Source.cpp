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
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = 'C';
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

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int numberOfLevel = 3;
bool endGame = 0;
int whichMap = 1;
int GWIDTH = 20;
int GHEIGHT = 15;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
vector<vector<char> > gBoard;
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

//紀錄現在的遊玩進度
void saveData();

void clearSaveFile();
void setupMap();
Trigger  gTrigger(5, 5, 10);
Trigger  gTrigger1;

int main(int argc, char** argv)
{

	cout << "you want to play from last record? (y/n)" << endl;
	char input;
	while (cin >> input) {
		if (input == 'n') {
			clearSaveFile();
			do {
				cout << "which level you want to play?" << endl;
				cout << "input 1 to " << numberOfLevel << " number = > ";
			} while (cin >> whichMap && (whichMap < 1 || whichMap > numberOfLevel));
			break;
		}
		else if (input == 'y') {
			break;
		}
	}
	goto start;
startAgain:
	clearSaveFile();
	do {
		cout << "which level you want to play?" << endl;
		cout << "input 1 to " << numberOfLevel << " number = > ";
	} while (cin >> whichMap && (whichMap < 1 || whichMap > numberOfLevel));
start:
	system("cls");
	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[6];
	
	// Setup a clear dungeon
	setupBoard();
finish:
	if (endGame) {
		cout << "you finished the game!" << endl;
		cout << "Do you want to play again? (y/n) " << endl;
		char input;
	input:
		cin >> input;
		if (input == 'y') {
			endGame = 0;
			whichMap = 1;
			clearSaveFile();
			system("cls");
			goto startAgain;
		}
		else if (input == 'n') {
			clearSaveFile();
			goto over;
		}
		else {
			cout << "input \"y\" or \"n\" " << endl;
			goto input;
		}
	}

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
	while (!gKeyState[ValidInput::EESC] && !endGame) {
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
	if (endGame) {
		goto finish;
	}
over:
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
	ifstream file;
	ifstream map;
	file.open("../saves/save.txt");
	map.open("../saves/level.txt");
	// error messages
	if (file.fail()) {
		cout << "fail to open save.txt" << endl;
	}
	if (map.fail()) {
		cout << "fail to open level.txt" << endl;
	}

	// 先讀取之前玩到的關卡
	if (file.good()) {
		file >> whichMap;
	}
	if (whichMap > numberOfLevel) {
		endGame = 1;
		return;
	}
	// 把那關卡的預設參數先打好
	int m = 0;
	while (map.good()) {
		//cout << "open map" << endl;
		string buf;
		getline(map, buf);
		if (buf == "map") {
			map >> m;
			if (m == whichMap) break;
		}
	}

	map >> GHEIGHT >> GWIDTH;
	int heroX, heroY;
	map >> heroX >> heroY;
	//cout << heroX << " " << heroY << endl;
	gHero.setPos(heroX, heroY);
	// read and set Creature position
	int creX, creY;
	map >> creX >> creY;
	gCreature.setPos(creX, creY);
	// read and set Trigger position
	int t1X, t1Y;
	int t2X, t2Y;
	map >> t1X >> t1Y;
	map >> t2X >> t2Y;
	gTrigger.setPos(t1X, t1Y);
	gTrigger1.setPos(t2X, t2Y);
	int exp1, exp2;
	map >> exp1 >> exp2;
	//cout << exp1 << " " << exp2 << endl;
	gTrigger.SetAmount(exp1);
	gTrigger1.SetAmount(exp2);

	//cout << "peek " << map.peek() << endl;
	// 把之前的進度讀取到程式裡面
	while (file.good()) {
		// read and set Hero position
		int heroX, heroY;
		file >> heroX >> heroY;
		gHero.setPos(heroX, heroY);
		// read and set Creature position
		int creX, creY;
		file >> creX >> creY;
		gCreature.setPos(creX, creY);
		// read and set Trigger position
		int t1X, t1Y;
		int t2X, t2Y;
		file >> t1X >> t1Y;
		file >> t2X >> t2Y;
		gTrigger.setPos(t1X, t1Y);
		gTrigger1.setPos(t2X, t2Y);
		// read and set additional information
		int lvl, exp, hp;
		file >> lvl >> exp >> hp;
		gHero.setLevel(lvl);
		gHero.setExp(exp);
		gHero.setHp(hp);
		system("CLS");
	}
	//cout << GHEIGHT << GWIDTH << endl;

	gBoard.clear();
	gBoard = vector<vector<char>>(GHEIGHT, vector<char>(GWIDTH));
	//cout << gBoard.size() << " " << gBoard[0].size() << endl;
	map.ignore();
	for (int i = 0; i < gBoard.size(); i++) {
		string line;
		getline(map, line);
		for (int j = 0; j < gBoard[i].size(); j++) {
			gBoard[i][j] = line[j];
		}
	}
	file.close();
	map.close();
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	vector<vector<char> > drawBoard(GHEIGHT+1,vector<char>(GWIDTH+1));

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

	Position t1 = gTrigger1.getPos();
	drawBoard[t1.y][t1.x] = gTrigger1.getIcon();

	// Hero loses health when steps on creature
	/*Please implement your code here*/

	if (h.x == c.x && h.y == c.y)
	{
		gHero.damage(1);
	}



	/************************************************************************/


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
	std::cout << "Heo has " << gHero.getHealth() << " health\n";
	std::cout << "Use arrow key to moved Hero @\n";
	std::cout << "Use Every time you step on a trigger T. the hero gets " << gTrigger.getExpAmount() << " or " << gTrigger1.getExpAmount() << " EXP points\n";
	std::cout << "Press ESC key to exit\n";
	cout << "map is " << whichMap << endl;
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
	if (gHero.getPos().x == GWIDTH - 2 && gHero.getPos().y == GHEIGHT - 2) {
		// 進入下一關
		whichMap++;
		ifstream map;
		map.open("../saves/level.txt");
		if (map.fail()) {
			cout << "fail to go to next level." << endl;
		}
		int m = 0;
		while (map.good()) {
			//cout << "open map" << endl;
			string buf;
			getline(map, buf);
			if (buf == "map") {
				map >> m;
				if (m == whichMap) break;
			}
			else if (buf == "end") {
				endGame = 1;
				break;
			}
		}
		if (endGame == 0) {
			map >> GHEIGHT >> GWIDTH;
			int heroX, heroY;
			map >> heroX >> heroY;
			//cout << heroX << " " << heroY << endl;
			gHero.setPos(heroX, heroY);
			// read and set Creature position
			int creX, creY;
			map >> creX >> creY;
			gCreature.setPos(creX, creY);
			// read and set Trigger position
			int t1X, t1Y;
			int t2X, t2Y;
			map >> t1X >> t1Y;
			map >> t2X >> t2Y;
			gTrigger.setPos(t1X, t1Y);
			gTrigger1.setPos(t2X, t2Y);
			int exp1, exp2;
			map >> exp1 >> exp2;
			//cout << exp1 << " " << exp2 << endl;
			gTrigger.SetAmount(exp1);
			gTrigger1.SetAmount(exp2);

			gBoard.clear();
			gBoard = vector<vector<char>>(GHEIGHT, vector<char>(GWIDTH));
			//cout << gBoard.size() << " " << gBoard[0].size() << endl;
			map.ignore();
			for (int i = 0; i < gBoard.size(); i++) {
				string line;
				getline(map, line);
				for (int j = 0; j < gBoard[i].size(); j++) {
					gBoard[i][j] = line[j];
				}
			}

		}
		map.close();
	}

	gCreature.update(gHero.getPos());
	gTrigger.update(gHero);
	gTrigger1.update(gHero);
	draw();
	drawInfo();
	saveData();
}
void saveData() {
	ofstream file;
	file.open("../saves/save.txt");
	if (file.fail()) {
		cout << "fail to open save.txt." << endl;
		return;
	}
	file.clear();
	file << whichMap << endl;
	file << gHero.getPos().x << " " << gHero.getPos().y << endl;
	file << gCreature.getPos().x << " " << gCreature.getPos().y << endl;
	file << gTrigger.getPos().x << " " << gTrigger.getPos().y << endl;
	file << gTrigger1.getPos().x << " " << gTrigger1.getPos().y << endl;
	file << gHero.getLevel() << " " << gHero.getExp() << " " << gHero.getHealth() << endl;
	file.close();
}

void clearSaveFile() {
	ofstream file;
	file.open("../saves/save.txt");
	if (file.fail()) {
		cout << "fail to open save.txt." << endl;
		return;
	}
	file.clear();
	file.close();
}

