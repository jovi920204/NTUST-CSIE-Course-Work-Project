// Name: ±i∫Õ≈Ô
// Date: March, 3 , 2022  
// Last Update: March, 5 , 2022  
// Problem statement: Greatest Common Divisor
#include <iostream>
using namespace std;

int GCD(int a, int b);

int main() {
	int a, b;
	while (cin >> a >> b) {
		cout << GCD(a, b) << endl;
	}

	return 0;
}

int GCD(int a, int b) {
	if (a == 0) return b;
	if (a > b) return GCD(a % b, b);
	else {
		return GCD(b % a, a);
	}
}