// Name: ±i∫Õ≈Ô
// Date: May, 10 , 2022  
// Last Update: May, 10 , 2022  
// Problem statement: Matrix Multiplication
#include <iostream>
#include <vector>

using namespace std;

// matrix multiplication 
void matrixMultiplication(vector<vector<int>>& m1, vector<vector<int>>& m2, vector<vector<int>>& ans);

int main() {
	int row1, col1, row2, col2;
	while (cin >> row1 >> col1 >> row2 >> col2) {
		vector<vector<int> > m1(row1, vector<int>(col1)); // matrix 1
		vector<vector<int> > m2(row2, vector<int>(col2)); // matrix 2
		vector<vector<int> > ans(row1, vector<int>(col2)); // answer matrix
		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col1; j++) {
				cin >> m1[i][j];
			}
		}
		for (int i = 0; i < row2; i++) {
			for (int j = 0; j < col2; j++) {
				cin >> m2[i][j];
			}
		}
		// if column of matrix 1 is not equal row of matrix 2, then these two matrices can not multiple together.
		if (col1 != row2) {
			cout << "Matrix multiplication failed." << endl;
		}
		else {
			matrixMultiplication(m1, m2, ans);
			for (int i = 0; i < row1; i++) {
				for (int j = 0; j < col2; j++) {
					if (j != col2 - 1) {
						cout << ans[i][j] << " ";
					}
					else {
						cout << ans[i][j];
					}
				}
				cout << endl;
			}
		}
	}
	return 0;
}

void matrixMultiplication(vector<vector<int>>& m1, vector<vector<int>>& m2, vector<vector<int>>& ans) {
	
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m2[0].size(); j++) {
			for (int r = 0; r < m1[0].size(); r++) {
				ans[i][j] += m1[i][r] * m2[r][j];
			}
		}
	}
}