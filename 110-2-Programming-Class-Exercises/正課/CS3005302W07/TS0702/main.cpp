// Name: ±i∫Õ≈Ô
// Date: March, 31 , 2022  
// Last Update: March, 31 , 2022  
// Problem statement: Array to integer
#include <iostream>
#include "Atoi.h"

int main() {
	string beTrans;

	while (cin >> beTrans) {
		Atoi atoi(beTrans + "20");
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}

		atoi.SetString(beTrans);
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}
	}

	return 0;
}