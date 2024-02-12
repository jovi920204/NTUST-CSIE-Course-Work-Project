
// Name: 張睿麟
// Date: March, 2 , 2022  
// Last Update: March, 2 , 2022  
// Problem statement: Text-based histogram
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ifstream inputFile; // 輸入檔案變數
	ofstream outputFile;// 輸出檔案變數
	inputFile.open("grade.txt");
	outputFile.open("grades.Output");
	while (inputFile.good()) { //直到把輸入檔案讀完就跳出迴圈
		char buffer[500]; // 宣告暫存的緩衝空間
		inputFile.getline(buffer, 499);
		vector<int> count(6);
		for (int i = 0; i < strlen(buffer); i++) {
			if (isdigit(buffer[i])) { // 如果得到的值是數字，就存到vector中
				count[buffer[i] - '0']++;
			}
		}
		for (int i = 0; i < 6; i++) { // 把vector存的值寫入outputFile裡面
			outputFile << count[i] << " grade(s) of " << i << "\n";
		}
	}
	inputFile.close();
	outputFile.close();
	return 0;
}