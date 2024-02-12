// Name: ±i∫Õ≈Ô
// Date: Feb,  , 2022  
// Last Update: Feb, 22 , 2022  
// Problem statement: Computes the average and standard deviation
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
	for (double n; cin >> n;) {
		vector<double> v(n);
		// input all the numbers to vector v;
		for (double& i : v)
			cin >> i;
		//average
		double sum = 0;
		double average = 0;
		for (int i = 0; i < n; i++) {
			sum += v[i];
		}
		average = sum / n;
		//count standard deviation
		double staDev = 0; // the number of standard deviation
		for (int i = 0; i < n; i++) {
			staDev += (v[i] - average) * (v[i] - average);
		}
		staDev /= n;
		staDev = sqrt(staDev);
		cout << "Average:" << average << "\t" << "Standard deviation:" << staDev << "\n";
	}

	return 0;
}