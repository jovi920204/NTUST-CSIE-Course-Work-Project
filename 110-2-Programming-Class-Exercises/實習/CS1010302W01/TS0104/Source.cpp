// Name: ±i∫Õ≈Ô
// Date: Feb, 17 , 2022  
// Last Update: Feb, 17 , 2022  
// Problem statement: Input/Output 1
#include <iostream>
using namespace std;

int main() {
	string input;
	while (cin >> input) {
		// if length of input is less than 10 characters, have to fill in 10 - length of input.
		if (input.length() <= 10) {
			for (int i = 0; i < 10 - input.length(); i++) {
				cout << " ";
			}
		}
		cout << input << endl;
	}
	return 0;
}