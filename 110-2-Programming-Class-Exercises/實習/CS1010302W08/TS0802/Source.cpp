// Name: ±i∫Õ≈Ô
// Date: April, 7 , 2022  
// Last Update: April, 7 , 2022  
// Problem statement: Matrix Multiplication
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int rowA, colA, rowB, colB;
	cin >> rowA >> colA >> rowB >> colB;
	vector<vector<int> > matrixA(rowA, vector<int>(colA));
	vector<vector<int> > matrixB(rowB, vector<int>(colB));
	vector<vector<int> > answer(rowA, vector<int>(colB));
	for (int i = 0; i < rowA; i++) {
		for (int j = 0; j < colA; j++) {
			cin >> matrixA[i][j];
		}
	}
	for (int i = 0; i < rowB; i++) {
		for (int j = 0; j < colB; j++) {
			cin >> matrixB[i][j];
		}
	}
	if (colA != rowB) {
		cout << "Matrix multiplication failed." << endl;
	}
	else {
		for (int i = 0; i < rowA; i++) {
			for (int j = 0; j < colB; j++) {
				int sum = 0;
				for (int r = 0; r < colA; r++) {
					sum += matrixA[i][r] * matrixB[r][j];
				}
				answer[i][j] = sum;
			}
		}
		for (int i = 0; i < answer.size(); i++) {
			for (int j = 0; j < answer[i].size(); j++) {
				if (j == answer[i].size() - 1) {
					cout << answer[i][j];
				}
				else {
					cout << answer[i][j] << " ";
				}
			}
			if (i != answer.size() - 1) {
				cout << endl;
			}
		}
	}
}