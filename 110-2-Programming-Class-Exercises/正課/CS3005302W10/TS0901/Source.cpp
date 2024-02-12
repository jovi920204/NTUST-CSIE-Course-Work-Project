// Name: ±i∫Õ≈Ô
// Date: April, 20 , 2022  
// Last Update: April, 20 , 2022  
// Problem statement: The Translation Machine
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// if letterA can be replaced with letterB return 1, otherwise return 0
bool canReplace(vector<string>& dic, char& letterA, char& letterB, map<char, int>& count);

int main() {
	int m, n;
	// m is the number of translations of letters 
	// n is the number of word pairs
	while (cin >> m >> n) {
		if (m == 0 && n == 0) break;
		vector<string> dic(128); // dictionary which is store the replacing words
		for (int i = 0; i < m; i++) {
			char letterA, letterB;
			cin >> letterA >> letterB;
			dic[letterA] += letterB;
		}
		for (int i = 0; i < n; i++) {
			bool sameWord = false;
			string wordA, wordB;
			cin >> wordA >> wordB;
			if (wordA.length() == wordB.length()) {
				int j = 0;
				for (j = 0; j < wordA.length(); j++) {
					map<char, int> count; // it is for avoiding infinite loop
					if (canReplace(dic, wordA[j], wordB[j], count)) { // using the available translations zero or more times
						continue;
					}
					else {
						cout << "no" << endl;
						break;
					}
				}
				// represent that wordA is equal to wordB
				if (j == wordA.length()) {
					cout << "yes" << endl;
				}
			}
			else {
				cout << "no" << endl;
			}
		}
	}
	return 0;
}

bool canReplace(vector<string>& dic, char& letterA, char& letterB , map<char, int>& count) {

	// if letterA was emerged more than twice, we can kown that program is into infinite loop, so return 0 to break.
	if (count[letterA] != 0) return 0;

	if (letterA == letterB) return 1;
	count[letterA]++;
	char start = letterA;
	int index = 0;
	// to trivial all the availeble letter can be replaced
	while (index < dic[start].length()) {
		if (canReplace(dic, dic[start][index], letterB, count)) {
			return 1;
		}
		index++;
	}
	return 0;
}
