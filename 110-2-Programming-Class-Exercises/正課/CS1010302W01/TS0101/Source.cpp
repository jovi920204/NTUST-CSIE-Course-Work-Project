// Name: ±i∫Õ≈Ô
// Date: Feb, 17 , 2022  
// Last Update: Feb, 17 , 2022  
// Problem statement: Compute the squre root  
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	long double n;
	while (cin >> n) {
		long double previousGuess = n; 
		long double nextGuess = n / 2; 
		long double r;
		// If previousGuess substract nexGuess bigger than 0.01, then continue to calculate.
		while (abs(previousGuess - nextGuess) >= 0.01) {
			previousGuess = nextGuess;
			r = n / previousGuess;
			nextGuess = (previousGuess + r) / 2;
		}
		cout << setprecision(2) << fixed << nextGuess << endl;
	}
	return 0;
}