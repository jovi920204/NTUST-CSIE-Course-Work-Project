// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 28 , 2022  
// Problem statement: N Dim Vector
#include<iostream>
#include "VecNf.h"
using namespace std;

int main() {
	VecNf empty;
	float a_value[] = { 3.0, 2.0 };
	float b_value[] = { 1, 2, 3 };
	float c_value[] = { 6, 5, 4 };
	VecNf A(a_value, 2);
	VecNf B(b_value, 3);
	VecNf C(c_value, 3);
	VecNf T;
	T = A; // Assignment
	for (int i = 0; i < T.Size(); i++) {
		cout << T[i] << " ";
	} cout << endl;

	T = B; // Assignment
	for (int i = 0; i < T.Size(); i++) {
		cout << T[i] << " ";
	} cout << endl;

	T = B + C + A; // Vector addition
	for (int i = 0; i < T.Size(); i++) {
		cout << T[i] << " ";
	} cout << endl;
	
	cout << C * B << endl; // Scale

	cout << A * C << endl; // Inconsistent
	return 0;

}