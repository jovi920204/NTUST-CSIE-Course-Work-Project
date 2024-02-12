// Name: ±i∫Õ≈Ô
// Date: Feb, 17 , 2022  
// Last Update: Feb, 17 , 2022  
// Problem statement: ComputeHMS
#include <iostream>
using namespace std;

int main() {
	unsigned long long A;
	while (cin >> A) {
		unsigned long long hours;
		unsigned long long minutes;
		unsigned long long seconds;
		seconds = A % 60;
		A /= 60;
		minutes = A % 60;
		A /= 60;
		hours = A;
		cout << hours << " hours " << minutes << " minutes and " << seconds << " seconds" << endl;
	}
	return 0;
}