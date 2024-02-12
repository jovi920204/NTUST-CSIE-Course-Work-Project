// Name: 張睿麟
// Date: April, 27 , 2022  
// Last Update: April, 27 , 2022  
// Problem statement: Word game
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// whether next step can walk 
bool canWalk(int i, int j);

// weather the word in the words.txt is valid
bool canFind(int i, int j, int index, string& input);

// Use puzzle to store 4 by 4 table 
vector<vector<char> > puzzle(4, vector<char>(4));

// Use used to check position i,j in the puzzle is used or not
vector<vector<bool> > used(4, vector<bool>(4));

int main() {
	while (1) {
		//input
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> puzzle[i][j];
			}
		}

		// input is End Of File, break the program.
		if (cin.eof()) {
			break;
		}
		ifstream file;
		file.open("words.txt");
		
		// trivial all the string in the words.txt
		while (file.good()) {
		start:
			string input;
			getline(file, input);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {

					// find a word can match with the position i,j in the puzzle
					if (puzzle[i][j] == input[0]) {
						used = vector<vector<bool> >(4, vector<bool>(4));
						if (canFind(i, j, 0, input)) {
							cout << input << endl;
							goto start;
						}
					}
				}
			}
		}
		cout << endl;
		file.close();
	}
}

bool canFind(int i, int j, int index, string& input) {
	// if the position i,j is used, then return 0.
	if (used[i][j] == 1) return 0;

	// if the index equal to size of input - 1, then we found it is valid
	if (index == input.size() - 1) {
		return 1;
	}
	
	used[i][j] = 1;

	// 下一個要走的座標合法且與下一個input的字元相同, 尋找8次
	if (canWalk(i + 1, j) && puzzle[i + 1][j] == input[index + 1]) {
		if (canFind(i + 1, j, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i - 1, j) && puzzle[i - 1][j] == input[index + 1]) {
		if (canFind(i - 1, j, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i, j + 1) && puzzle[i][j + 1] == input[index + 1]) {
		if (canFind(i, j + 1, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i, j - 1) && puzzle[i][j - 1] == input[index + 1]) {
		if (canFind(i, j - 1, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i + 1, j + 1) && puzzle[i + 1][j + 1] == input[index + 1]) {
		if (canFind(i + 1, j + 1, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i + 1, j - 1) && puzzle[i + 1][j - 1] == input[index + 1]) {
		if (canFind(i + 1, j - 1, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i - 1, j + 1) && puzzle[i - 1][j + 1] == input[index + 1]) {
		if (canFind(i - 1, j + 1, index + 1, input)) {
			return 1;
		}
	}
	if (canWalk(i - 1, j - 1) && puzzle[i - 1][j - 1] == input[index + 1]) {
		if (canFind(i - 1, j - 1, index + 1, input)) {
			return 1;
		}
	}
	return 0;
}

bool canWalk(int i, int j) {
	// if i and j are >=0 and < 4, is valid position in the puzzle.
	if ((i >= 0 && j >= 0) && (i < 4 && j < 4)){
		return 1;
	}
	else {
		return 0;
	}
}