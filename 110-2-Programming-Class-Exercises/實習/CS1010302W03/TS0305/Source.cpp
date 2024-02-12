// Name: ±i∫Õ≈Ô
// Date: March, 3 , 2022  
// Last Update: March, 5 , 2022  
// Problem statement: Simple Drawing Program
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<vector<char> > board;
void drawSquare(int w, int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void drawBoard();
void drawTriangle(int w, int x, int y, string& type, int n, int m);
int main() {
	int m, n;
	cin >> n >> m;
	string command;
	board.resize(m, vector<char>(n, '*'));
	while (cin >> command) {
		// S <w> <x> <y> ==> Square
		if (command == "S") {
			int w, x, y;
			cin >> w >> x >> y;
			// is out of range or not
			if (x + w > n || y + w > m) {
				cout << "Out of range." << endl;
				cout << endl;
			}
			else {
				drawSquare(w, x, y);
				drawBoard();
			}

		}
		// T <w> <x> <y> <LU/LD/RU/RD> ==> Triangle
		else if (command == "T") {
			int w, x, y;
			string type;
			cin >> w >> x >> y >> type;
			// is out of range or not
			drawTriangle(w, x, y, type, n , m);
			
		}
		// L <x1> <y1> <x2> <y2> ==> Line
		else if (command == "L") {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			// is out of range or not
			if (x1 >= n || x2 >= n || y1 >= m || y2 >= m) {
				cout << "Out of range." << endl;
				cout << endl;
			}
			else {
				if (x2 < x1) {
					drawLine(x2, y2, x1, y1);
				}
				else {
					drawLine(x1, y1, x2, y2);
				}
				drawBoard();
			}

		}
		// EXIT
		else {
			break;
		}
	}

	return 0;
}
void drawBoard() {
	for (auto val1 : board) {
		for (auto val2 : val1) {
			cout << val2;
		}
		cout << endl;
	}
	cout << endl;
}
void drawSquare(int w, int x, int y) {
	for (int i = x; i < x + w; i++) {
		for (int j = y; j < y + w; j++) {
			board[j][i] = 'X';
		}
	}
}

void drawLine(int x1, int y1, int x2, int y2) {
	if (x1 == x2) { //straight line
		if (y1 > y2) {
			swap(y1, y2);
		}
		for (int i = y1; i <= y2; i++) {
			board[i][x1] = 'X';
		}
	}
	else if (y1 == y2) { //straight line
		if (x1 > x2) {
			swap(x1, x2);
		}
		for (int i = x1; i <= x2; i++) {
			board[y1][i] = 'X';
		}
	}
	else {
		if (x1 > x2) {
			swap(y1, y2);
			swap(x1, x2);
		}
		if (y1 > y2) {
			for (int i = x1, j = y1; i <= x2; i++, j--) {
				//cout << "x,y = " << i << " " << j << endl;
				board[j][i] = 'X';
			}
		}
		else {
			for (int i = x1, j = y1; i <= x2; i++, j++) {
				//cout << "x,y = " << i << " " << j << endl;
				board[j][i] = 'X';
			}
		}
		
	}
}

void drawTriangle(int w, int x, int y, string& type, int n, int m) {
	if (type == "RD") {
		if (x + w - 1 >= n || y + w - 1 >= m) {
			cout << "Out of range." << endl;
			cout << endl;
		}
		else {
			for (int i = y, count = 0; i < y + w; i++, count++) {
				for (int j = x; j < x + w - count; j++) {
					board[i][j] = 'X';
				}
			}
			drawBoard();
		}
	}
	else if (type == "LD") {
		if (x - w + 1 < 0 || y + w - 1 >= m) {
			cout << "Out of range." << endl;
			cout << endl;
		}
		else {
			for (int i = y, count = 0; i < y + w; i++, count++) {
				for (int j = x; j > x - w + count; j--) {
					board[i][j] = 'X';
				}
			}
			drawBoard();
		}
	}
	else if (type == "RU") {
		if (x + w - 1 >= n || y - w + 1 < 0) {
			cout << "Out of range." << endl;
			cout << endl;
		}
		else {
			for (int i = y, count = 0; i > y - w; i--, count++) {
				for (int j = x; j < x + w - count; j++) {
					board[i][j] = 'X';
				}
			}
			drawBoard();
		}
	}
	else if (type == "LU") {
		if (x - w + 1 < 0 || y - w + 1 < 0) {
			cout << "Out of range." << endl;
			cout << endl;
		}
		else {
			for (int i = y, count = 0; i > y - w; i--, count++) {
				for (int j = x; j > x - w + count; j--) {
					board[i][j] = 'X';
				}
			}
			drawBoard();
		}
	}
}