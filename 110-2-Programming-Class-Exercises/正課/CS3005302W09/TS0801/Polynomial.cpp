// Name: 張睿麟
// Date: April, 19 , 2022  
// Last Update: April, 19 , 2022  
// Problem statement: Design Polynomial Class
#include "Polynomial.h"


Polynomial::Polynomial() {
}

Polynomial::Polynomial(double* param, int _size)
{
	for (int i = 0; i < _size; i++) {
		p.push_back(param[i]);
	}
}

Polynomial::Polynomial(const Polynomial& poly)
{
	p = poly.p;
}

int Polynomial::mySize()
{
	return p.size();
}

const Polynomial Polynomial::operator=(const Polynomial& poly)
{
	p.clear();
	for (auto val : poly.p) {
		p.push_back(val);
	}
	return *this;
}

double& Polynomial::operator[](int index)
{
	if (index >= p.size()) {
		for (int i = 0; i < index - p.size() + 1; i++) {
			p.push_back(0);
		}
	}
	return p[index];
}


double evaluate(const Polynomial& poly, const double& var)
{
	double ans = 0;
	for (int i = 0; i < poly.p.size(); i++) {
		ans += poly.p[i] * pow(var, i);
	}
	return ans;
}

const Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2)
{
	Polynomial poly;
	if (poly1.p.size() > poly2.p.size()) {
		for (int i = 0; i < poly1.p.size(); i++) {
			if (i >= poly2.p.size()) {
				poly.p.push_back(poly1.p[i]);
			}
			else {
				poly.p.push_back(poly1.p[i] + poly2.p[i]);
			}
		}
	}
	else if (poly1.p.size() < poly2.p.size()) {
		for (int i = 0; i < poly2.p.size(); i++) {
			if (i >= poly1.p.size()) {
				poly.p.push_back(poly2.p[i]);
			}
			else {
				poly.p.push_back(poly1.p[i] + poly2.p[i]);
			}
		}
	}
	else {
		for (int i = 0; i < poly1.p.size(); i++) {
			poly.p.push_back(poly1.p[i] + poly2.p[i]);
		}
	}
	poly = update(poly);
	return poly;
}

const Polynomial operator+(double value, const Polynomial& poly2)
{
	Polynomial poly(poly2);
	poly.p[0] += value;
	poly = update(poly);
	return poly;
}

const Polynomial operator+(const Polynomial& poly1, double value)
{
	Polynomial poly(poly1);
	poly.p[0] += value;
	poly = update(poly);
	return poly;
}

const Polynomial operator-(const Polynomial& poly1, const Polynomial& poly2)
{
	Polynomial poly;
	if (poly1.p.size() > poly2.p.size()) {
		for (int i = 0; i < poly1.p.size(); i++) {
			if (i >= poly2.p.size()) {
				poly.p.push_back(poly1.p[i]);
			}
			else {
				poly.p.push_back(poly1.p[i] - poly2.p[i]);
			}
		}
	}
	else if (poly1.p.size() < poly2.p.size()) {
		for (int i = 0; i < poly2.p.size(); i++) {
			if (i >= poly1.p.size()) {
				poly.p.push_back(-poly2.p[i]);
			}
			else {
				poly.p.push_back(poly1.p[i] - poly2.p[i]);
			}
		}
	}
	else {
		for (int i = 0; i < poly1.p.size(); i++) {
			poly.p.push_back(poly1.p[i] - poly2.p[i]);
		}
	}
	poly = update(poly);
	return poly;
}

const Polynomial operator-(double value, const Polynomial& poly2)
{
	Polynomial poly(poly2);
	for (int i = 0; i < poly.p.size(); i++) {
		poly.p[i] = -poly2.p[i];
	}
	poly.p[0] = value - poly2.p[0];
	poly = update(poly);
	return poly;
}

const Polynomial operator-(const Polynomial& poly1, double value)
{
	Polynomial poly(poly1);
	poly.p[0] -= value;
	poly = update(poly);
	return poly;
}

const Polynomial operator*(const Polynomial& poly1, const Polynomial& poly2)
{
	Polynomial poly;
	poly.p = vector<double>(poly1.p.size() + poly2.p.size() - 1, 0);
	for (int i = 0; i < poly1.p.size(); i++) {
		for (int j = 0; j < poly2.p.size(); j++) {
			poly.p[i + j] += poly1.p[i] * poly2.p[j];
		}
	}
	poly = update(poly);
	return poly;
}

const Polynomial operator*(double value, const Polynomial& poly2)
{
	Polynomial poly(poly2);
	for (int i = 0; i < poly.p.size(); i++) {
		poly.p[i] = value * poly2.p[i];
	}
	poly = update(poly);
	return poly;
}

const Polynomial operator*(const Polynomial& poly1, double value)
{
	Polynomial poly(poly1);
	for (int i = 0; i < poly.p.size(); i++) {
		poly.p[i] = value * poly1.p[i];
	}
	poly = update(poly);
	return poly;
}

// 當最高次方項係數為零的時候，要把它從vector當初刪除
Polynomial update(const Polynomial& poly)
{
	Polynomial result = poly;
	while (result.p[result.p.size() - 1] == 0) {
		result.p.erase(result.p.begin() + result.p.size() - 1);
	}
	return result;
}

