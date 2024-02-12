// Name: ±i∫Õ≈Ô
// Date: April, 1 , 2022  
// Last Update: April, 1 , 2022  
// Problem statement: Seven-segment Display
#include <iostream>
#include <string>
using namespace std;


int main() {
	string part1[] = { " _ ","   "," _ "," _ ","   "," _ "," _ "," _ "," _ "," _ " };
	string part2[] = { "| |","  |"," _|"," _|","|_|","|_ ","|_ ","  |","|_|","|_|" };
	string part3[] = { "|_|","  |","|_ "," _|","  |"," _|","|_|","  |","|_|"," _|" };
	string input;
	while (getline(cin, input)) {
		string pureInput = "";
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				continue;
			}
			pureInput += input[i];
		}
		for (int i = 0; i < pureInput.length(); i++) {
			cout << part1[pureInput[i] - '0'];
		}
		cout << endl;
		for (int i = 0; i < pureInput.length(); i++) {
			cout << part2[pureInput[i] - '0'];
		}
		cout << endl;
		for (int i = 0; i < pureInput.length(); i++) {
			cout << part3[pureInput[i] - '0'];
		}
		cout << endl;
	}


	return 0;
}

/*
 _     _  _     _  _  _  _  _  _
| |  | _| _||_||_ |_   ||_||_|| |
|_|  ||_  _|  | _||_|  ||_| _||_|




*/