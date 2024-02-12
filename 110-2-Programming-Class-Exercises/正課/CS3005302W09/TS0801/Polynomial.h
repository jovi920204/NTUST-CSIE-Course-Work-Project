// Name: �i����
// Date: April, 19 , 2022  
// Last Update: April, 19 , 2022  
// Problem statement: Design Polynomial Class
#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Polynomial
{
public:
	Polynomial();
	Polynomial(double* param, int _size);
	Polynomial(const Polynomial& poly);
	int mySize();
	friend double evaluate(const Polynomial& poly, const double& var);
	const Polynomial operator=(const Polynomial& poly);
	double& operator[](int index);
	friend const Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2);
	friend const Polynomial operator+(double value, const Polynomial& poly2);
	friend const Polynomial operator+(const Polynomial& poly1, double value);
	friend const Polynomial operator-(const Polynomial& poly1, const Polynomial& poly2);
	friend const Polynomial operator-(double value, const Polynomial& poly2);
	friend const Polynomial operator-(const Polynomial& poly1, double value);
	friend const Polynomial operator*(const Polynomial& poly1, const Polynomial& poly2);
	friend const Polynomial operator*(double value, const Polynomial& poly2);
	friend const Polynomial operator*(const Polynomial& poly1, double value);

	// ��̰����趵�Y�Ƭ��s���ɭԡA�n�⥦�qvector���R��
	friend Polynomial update(const Polynomial& poly);
	vector<double> p;
};


