// Name: ±i∫Õ≈Ô
// Date: Feb, 17 , 2022  
// Last Update: Feb, 17 , 2022  
// Problem statement: Compute Sphere Volume
#include <iostream>
#include <iomanip>
#define PI 3.14159265358979323846;
using namespace std;

int main() {
	double r;
	while (cin >> r) {
		// volume of sphere formula is "4 / 3 * PI * r * r * r"
		double answer = r * r * r * PI;
		answer = answer * 4 / 3;
		printf("%.6f\n", answer);
	}
	return 0;
}