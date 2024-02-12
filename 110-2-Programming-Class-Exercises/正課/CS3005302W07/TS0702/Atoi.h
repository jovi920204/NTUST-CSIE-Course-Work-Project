// Name: ±i∫Õ≈Ô
// Date: March, 31 , 2022  
// Last Update: March, 31 , 2022  
// Problem statement: Array to integer
#include <string>
#include <iostream>
using namespace std;

class Atoi {

private:
	string beTrans;
	
public:
	Atoi();
	Atoi(string s);
	void SetString(string s);
	const string GetString();
	int Length();
	bool IsDigital();
	int StringToInteger();

};