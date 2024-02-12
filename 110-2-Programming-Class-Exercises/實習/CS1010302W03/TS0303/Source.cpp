// Name: �i����
// Date: March, 3 , 2022  
// Last Update: March, 3 , 2022  
// Problem statement: Input_Output3
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int findDot(string &str){
	int i = 0;
	while (i < str.length()) {
		if (str[i] == '.') {
			return i;
		}	
		i++;
	}
	return 0;
}

int main() {
	string X;
	int M, N;
	char C;
	while (cin >> X >> M >> N >> C) {
		bool haveDot = false;
		int dotLocation = 0;
		vector<char> ans;
		// �M��p���I����m�A�p�G�S���N�]��0
		dotLocation = findDot(X);
		if (dotLocation > 0) haveDot = true;
		//��X�n�˱�N��H�~�A�������ɹs
		//�P�_���S���p�� ���פj��1
		if (haveDot) { //�N���p��
			if (N == 0) { // N == 0
				for (int i = 0; i < dotLocation; i++) {
					ans.push_back(X[i]);
				}
			}
			else { // N > 0 �çP�_�ݤ��ݭn�ɹs
				if ((X.length() - dotLocation - 1) < N) { //�p�Ƴ�������N
					for (int i = 0; i < X.length(); i++) {
						ans.push_back(X[i]);
					}
					for (int i = 0; i < N - (X.length() - dotLocation - 1); i++) {
						ans.push_back('0');
					}
				}
				else {
					for (int i = 0; i < N + dotLocation + 1; i++) {
						ans.push_back(X[i]);
					}
				}
					
			}
		}
		else { // �S�p�Ƴ���
			//N == 0
			if (N == 0) {
				for (int i = 0; i < X.length(); i++) {
					ans.push_back(X[i]);
				}
			}
			//N > 0
			else { 
				for (int i = 0; i < X.length(); i++) {
					ans.push_back(X[i]);
				}
				ans.push_back('.');
				// �ɹs
				for (int i = 0; i < N; i++) {
					ans.push_back('0');
				}
			}
				
		}
		

		// �p�GX������(�]�t�t��)�p��M�A�H�ܼ�C���r���b�e���ɻ�
		if (ans.size() < M) {
			for (int i = 0; i < M - ans.size(); i++) {
				cout << C;
			}
		}
		for (auto val : ans) {
			cout << val;
		}
		cout << endl;
	}
	return 0;
}

/// 999999.999999999 16 9 X