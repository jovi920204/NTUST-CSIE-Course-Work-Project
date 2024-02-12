// Name: ±i∫Õ≈Ô
// Date: Feb, 24 , 2022  
// Last Update: Feb, 24 , 2022  
// Problem statement: Compute The Tax
#include <iostream>
using namespace std;

int main() {
	double n;
	// input
	while (cin >> n) {
		double result = 0;
		if (n <= 750) {
			result = n * 0.01;
		}
		else if (n <= 2250) {
			result = 7.50 + (n - 750) * 0.02;
		}
		else if (n <= 3750) {
			result = 37.50 + (n - 2250) * 0.03;
		}
		else if (n <= 5250) {
			result = 82.50 + (n - 3750) * 0.04;
		}
		else if (n <= 7000) {
			result = (n - 5250) * 0.05 + 142.50;
		}
		else {
			result = (n - 7000) * 0.06 + 230;
		}
		printf("%.2f\n", result);
	}
	return 0;
}