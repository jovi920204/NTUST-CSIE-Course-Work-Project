// Name: ±i∫Õ≈Ô
// Date: April, 1 , 2022  
// Last Update: April, 1 , 2022  
// Problem statement: Form Word
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;
class Form
{
private:
	string word;
	string fileName;
	vector<string> valid;
public:
	Form();
	void SetInputWord(string inputWord); // set input
	void ProcessInputWord(); // process input
	void SetFileName(string fileName); // set file name
	void Load_CompareWord(); // read-in data and compare
	void PrintFoundWords(); // print answers
};
