// Name: ±i∫Õ≈Ô
// Date: March, 10 , 2022  
// Last Update: March, 10 , 2022  
// Problem statement: Collatz Conjecture
#include <iostream>
using namespace std;

int calculation(int x, int count);

int main() {
	int a, b;
	while (cin >> a >> b) {
		int original_A = a;
		int original_B = b;
		if (a > b) {
			swap(a, b);
		}
		int maxCount = 0;
		int count = 1;
		for (int i = a; i <= b; i++) {
			count = 1;
			count = calculation(i, count);
			if (count > maxCount) {
				maxCount = count;
			}
		}
		cout << original_A << " " << original_B << " " << maxCount << endl;
	}
	return 0;
}

int calculation(int x, int count) {
	if (x == 1) return count;
	if (x % 2 == 0) {
		return calculation(x / 2, count + 1);
	}
	else {
		return calculation(3 * x + 1, count + 1);
	}
}