// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Number Game
#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

class NumberGame {
private:
	int intInput;
	string strInput;
	string fileName;
	vector<int> validNum;
public:
	void SetInput(int);
	void ProcessInput();
	void SetFileName(string);
	void LoadNumberList();
	void PrintAllValid();
	void Reset();
};