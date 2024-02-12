// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Number Game
#include "NumberGame.h"

void NumberGame::SetInput(int in)
{
	intInput = in;
}
void NumberGame::ProcessInput()
{
	strInput = to_string(intInput);
}

void NumberGame::SetFileName(string name)
{
	fileName = name;
}

void NumberGame::LoadNumberList()
{
	int len = strInput.length();
	int maxCom = pow(2.0, double(len));
	for (int i = 1; i < maxCom; i++) {
		bitset<32> digit(i);
		int sum = 1;
		for (int j = 0; j < len; j++) {
			if (digit[j] == 1) {
				
				sum *= (strInput[j]-'0');
			}
		}
		validNum.push_back(sum);
	}
	sort(validNum.begin(),validNum.end());
}

void NumberGame::PrintAllValid()
{
	ifstream file(fileName);
	int input;
	while (file >> input) {
		for (auto val : validNum) {
			//cout << val << endl;
			if (val == input) {
				cout << input << endl;
				break;
			}
			else if (input < val) {
				break;
			}
		}
	}
}

void NumberGame::Reset()
{
	intInput = 0;
	strInput = "";
	fileName = "";
	validNum.clear();
}
