// Name: ±i∫Õ≈Ô
// Date: Feb, 24 , 2022  
// Last Update: Feb, 24 , 2022  
// Problem statement: Computes the average and standard deviation
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
	int n;
	while (cin >> n) {
		// init
		int nameLenMax = 0;
		int salaryLenMax = 0;
		int bonusLenMax = 0;
		vector<string> name(n);
		vector<string> salary(n);
		vector<string> bonus(n);
		// input
		for (int i = 0; i < n; i++) {
			cin >> name[i] >> salary[i] >> bonus[i];
			// record the longest name, salary and bonus characters
			if (name[i].length() > nameLenMax) {
				nameLenMax = name[i].length();
			}
			if (salary[i].length() > salaryLenMax) {
				salaryLenMax = salary[i].length();
			}
			if (bonus[i].length() > bonusLenMax) {
				bonusLenMax = bonus[i].length();
			}
		}
		// output
		for (int i = 0; i < n; i++) {
			cout << setw(nameLenMax) << name[i] << "|" << setw(salaryLenMax + 2) << salary[i] << "|" << setw(bonusLenMax + 2) << bonus[i] << "\n";
		}

	}

	return 0;
}