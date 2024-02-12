// Name: ±i∫Õ≈Ô
// Date: Feb,  , 2022  
// Last Update: Feb, 22 , 2022  
// Problem statement: Leaderboard
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void getHighScore(vector<string>& name, vector<int>& score);

int main() {
	vector<string> name;
	vector<int> score;
	getHighScore(name, score);
	// output the result
	for (int i = 0; i < 3; i++) {
		cout << name[i] << "\n" << score[i] << "\n";
	}
	return 0;
}

void getHighScore(vector<string>& name, vector<int>& score) {
	ifstream inputStream;
	inputStream.open("scores.txt");
	int index = 0; // This variable is used to record how many are the students.
	char nameBuf[100];
	char scoreBuf[100];
	while (inputStream.good()) {
		int scoreBuf_int = 0;
		inputStream.getline(nameBuf, 99);
		inputStream.getline(scoreBuf, 99);
		//switch score from string to int.
		for (int i = strlen(scoreBuf) - 1, base = 1; i >= 0; i--, base *= 10) { // base is weight of decimal
			scoreBuf_int += (scoreBuf[i] - '0') * base;
		}
		name.push_back(nameBuf);
		score.push_back(scoreBuf_int);
		index++;
	}
	inputStream.close();
	// sort, using bubble sort
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index - i - 1; j++) {
			if (score[j] < score[j + 1]) {
				swap(score[j], score[j + 1]);
				swap(name[j], name[j + 1]);
			}
		}
	}
}

