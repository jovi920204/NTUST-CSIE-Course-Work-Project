// Name: ±i∫Õ≈Ô
// Date: April, 1 , 2022  
// Last Update: April, 1 , 2022  
// Problem statement: Cow calculation

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void fill(string& s);
void operation_A(string& s1, string& s2);
void operation_N(string& s1, string& s2);

int main() {
	int times;
	cin >> times;
	cout << "COWCULATIONS OUTPUT" << endl;
	while (times--) {
		string Num1;
		string Num2;
		char operation;
		cin >> Num1 >> Num2;
		//--------------------------
		// fill to 8 symbol
		fill(Num1);
		fill(Num2);
		//--------------------------

		for (int i = 0; i < 3; i++) {
			cin >> operation;
			if (operation == 'A') {
				operation_A(Num1, Num2);
			}
			else if (operation == 'R') {
				reverse(Num2.begin(), Num2.end());
				for (int i = 1; i < Num2.length(); i++) {
					Num2[i - 1] = Num2[i];
				}
				reverse(Num2.begin(), Num2.end());
				Num2[0] = 'V';
			}
			else if (operation == 'L') {
				for (int i = 1; i < Num2.length(); i++) {
					Num2[i - 1] = Num2[i];
				}
				reverse(Num2.begin(), Num2.end());
				Num2[0] = 'V';
				reverse(Num2.begin(), Num2.end());
			}
			else if (operation == 'N') {
				continue;
			}
		}
		string ans;
		cin >> ans;
		if (ans == Num2) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	cout << "END OF OUTPUT" << endl;


	return 0;
}

void fill(string& s) {
	if (s.length() < 8) {
		s = "V" + s;
		fill(s);
	}
	return;
}

void operation_A(string& s1, string& s2)
{
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
 	int carry = 0;
	for (int i = 0; i < 8; i++) {
		//cout << s1[i] << " " << s2[i] << carry << endl;
		if (s1[i] == 'V') {
			if (s2[i] == 'V') {
				if (carry) {
					s2[i] = 'U';
					carry = 0; 
				}
				else {
					s2[i] = 'V';
				}
			}
			else if (s2[i] == 'U') {
				if (carry) {
					s2[i] = 'C';
					carry = 0;
				}
				else {
					s2[i] = 'U';
				}

			}
			else if (s2[i] == 'C') {
				if (carry) {
					s2[i] = 'D';
					carry = 0;
				}
				else {
					s2[i] = 'C';
				}
			}
			else if (s2[i] == 'D') {
				if (carry) {
					s2[i] = 'V';
					carry = 1;
				}
				else {
					s2[i] = 'D';
				}
			}
		}
		else if (s1[i] == 'U') {
			if (s2[i] == 'V') {
				if (carry) {
					s2[i] = 'C';
					carry = 0;
				}
				else {
					s2[i] = 'U';
				}
			}
			else if (s2[i] == 'U') {
				if (carry) {
					s2[i] = 'D';
					carry = 0;
				}
				else {
					s2[i] = 'C';
				}

			}
			else if (s2[i] == 'C') {
				if (carry) {
					s2[i] = 'V';
					carry = 1;
				}
				else {
					s2[i] = 'D';
				}
			}
			else if (s2[i] == 'D') {
				if (carry) {
					s2[i] = 'U';
					carry = 1;
				}
				else {
					s2[i] = 'V';
					carry = 1;
				}
			}
		}
		else if (s1[i] == 'C') {
			if (s2[i] == 'V') {
				if (carry) {
					s2[i] = 'D';
					carry = 0;
				}
				else {
					s2[i] = 'C';
				}
			}
			else if (s2[i] == 'U') {
				if (carry) {
					s2[i] = 'V';
					carry = 1;
				}
				else {
					s2[i] = 'D';
				}

			}
			else if (s2[i] == 'C') {
				if (carry) {
					s2[i] = 'U';
					carry = 1;
				}
				else {
					s2[i] = 'V';
					carry = 1;
				}
			}
			else if (s2[i] == 'D') {
				if (carry) {
					s2[i] = 'C';
					carry = 1;
				}
				else {
					s2[i] = 'U';
					carry = 1;
				}
			}
		}
		else if (s1[i] == 'D') {
			if (s2[i] == 'V') {
				if (carry) {
					s2[i] = 'V';
					carry = 1;
				}
				else {
					s2[i] = 'D';
				}
			}
			else if (s2[i] == 'U') {
				if (carry) {
					s2[i] = 'U';
					carry = 1;
				}
				else {
					s2[i] = 'V';
					carry = 1;
				}

			}
			else if (s2[i] == 'C') {
				if (carry) {
					s2[i] = 'C';
					carry = 1;
				}
				else {
					s2[i] = 'U';
					carry = 1;
				}
			}
			else if (s2[i] == 'D') {
				if (carry) {
					s2[i] = 'D';
					carry = 1;
				}
				else {
					s2[i] = 'C';
					carry = 1;
				}
			}
		}
	}
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
}


void operation_N(string& s1, string& s2)
{
	
}
