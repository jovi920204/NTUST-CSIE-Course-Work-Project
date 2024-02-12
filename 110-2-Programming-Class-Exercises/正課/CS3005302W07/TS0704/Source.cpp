// Name: ±i∫Õ≈Ô
// Date: March, 31 , 2022  
// Last Update: March, 31 , 2022  
// Problem statement: Levenshtein Distance
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	string str1, str2;
	while (1) {
		getline(cin, str1);
		getline(cin, str2);
		str1 = " " + str1;
		str2 = " " + str2;
		vector<vector<int> > dp(str1.length());
		for (int i = 0; i < str1.length(); i++) {
			for (int j = 0; j < str2.length(); j++) {
				dp[i].push_back(0);
			}
		}
		for (int i = 0; i < str1.length(); i++) {
			for (int j = 0; j < str2.length(); j++) {
				int rl, ru, rs;
				if (i == 0 && j == 0) continue;
				if (j == 0) {
					dp[i][j] = dp[i - 1][j] + 1;
				}
				else if (i == 0) {
					dp[i][j] = dp[i][j - 1] + 1;
				}
				else {
					rl = dp[i][j - 1] + 1;
					ru = dp[i - 1][j] + 1;
					if (str1[i] == str2[j]) rs = dp[i - 1][j - 1];
					else {
						rs = dp[i - 1][j - 1] + 1;
					}
					dp[i][j] = min(rl, min(ru, rs));
				}
			}
		}
		if (cin.eof()) {
			break;
		}
		cout << dp[str1.length()-1][str2.length()-1] << endl;

	}


	return 0;
}