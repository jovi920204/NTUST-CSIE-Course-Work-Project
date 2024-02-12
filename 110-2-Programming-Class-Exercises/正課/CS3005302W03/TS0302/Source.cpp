
// Name: �i����
// Date: March, 2 , 2022  
// Last Update: March, 2 , 2022  
// Problem statement: Text-based histogram
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ifstream inputFile; // ��J�ɮ��ܼ�
	ofstream outputFile;// ��X�ɮ��ܼ�
	inputFile.open("grade.txt");
	outputFile.open("grades.Output");
	while (inputFile.good()) { //������J�ɮ�Ū���N���X�j��
		char buffer[500]; // �ŧi�Ȧs���w�ĪŶ�
		inputFile.getline(buffer, 499);
		vector<int> count(6);
		for (int i = 0; i < strlen(buffer); i++) {
			if (isdigit(buffer[i])) { // �p�G�o�쪺�ȬO�Ʀr�A�N�s��vector��
				count[buffer[i] - '0']++;
			}
		}
		for (int i = 0; i < 6; i++) { // ��vector�s���ȼg�JoutputFile�̭�
			outputFile << count[i] << " grade(s) of " << i << "\n";
		}
	}
	inputFile.close();
	outputFile.close();
	return 0;
}