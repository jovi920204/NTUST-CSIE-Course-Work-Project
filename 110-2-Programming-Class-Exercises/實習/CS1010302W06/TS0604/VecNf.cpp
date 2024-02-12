// Name: ±iºÍÅï
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: N Dim Vector
#include "VecNf.h"

VecNf::VecNf() {
	this->dim = 1;
	this->value.push_back(0.0f);
}
VecNf::VecNf(float* dest, int cnt) {
	this->dim = cnt;
	for (int i = 0; i < cnt; i++) {
		this->value.push_back(dest[i]);
	}
}
VecNf::VecNf(const VecNf& rhs) {
	this->dim = rhs.dim;
	this->value.resize(dim);
	for (int i = 0; i < this->dim; i++) {
		this->value[i] = rhs.value[i];
	}
}


VecNf& VecNf::operator=(const VecNf& result) {
	cout << "ASSIGNMENT!!!" << endl;
	this->dim = result.dim;
	this->value.resize(dim);
	for (int i = 0; i < dim; i++) {
		this->value[i] = result.value[i];
	}
	return *this;
}
VecNf operator+(const VecNf& x1, const VecNf& x2) {
	VecNf result = x1;
	if (x1.dim == x2.dim) {
		result.dim = x1.dim;
		for (int i = 0; i < x1.dim; i++) {
			result.value[i] = (x1.value[i] + x2.value[i]);
		}
		return result;
	}
	else {
		cout << "dimensions inconsistent" << endl;
		return result;
	}
}
VecNf operator-(const VecNf& x1, const VecNf& x2) {
	VecNf result = x1;
	if (x1.dim == x2.dim) {
		result.dim = x1.dim;
		for (int i = 0; i < x1.dim; i++) {
			result.value[i] = (x1.value[i] - x2.value[i]);
		}
		return result;
	}
	else {
		cout << "dimensions inconsistent" << endl;
		return result;
	}
}
float operator*(const VecNf& x1, const VecNf& x2) {
	float sum = 0;
	if (x1.dim == x2.dim) {
		for (int i = 0; i < x1.dim; i++) {
			sum += (x1.value[i] * x2.value[i]);
		}
		return sum;
	}
	else {
		cout << "dimensions inconsistent" << endl;
		return 0.0f;
	}
}
float& VecNf::operator[](int index) {
	return this->value[index];
}
int VecNf::Size() {
	return this->dim;
}

VecNf operator*(double s, VecNf& x) {
	VecNf result = x;
	for (int i = 0; i < x.dim; i++) {
		result.value[i] = (s * x.value[i]);
	}
	return result;
}
