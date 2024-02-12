// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 28 , 2022  
// Problem statement: N Dim Vector
#pragma once
#include <iostream>
#include <vector>

using namespace std;

class VecNf {
private:
	int dim;
	vector<float> value;

public:
	VecNf();
	VecNf(float* dest, int cnt);
	VecNf(const VecNf& rhs);
	VecNf& operator=(const VecNf& result);
	float& operator[](int index);
	friend VecNf operator+(const VecNf& x1, const VecNf& x2);
	friend VecNf operator-(const VecNf& x1, const VecNf& x2);
	friend float operator*(const VecNf& x1, const VecNf& x2);
	friend VecNf operator*(double s, VecNf& x);
	int Size();

};