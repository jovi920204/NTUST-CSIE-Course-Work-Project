// Name: 張睿麟
// Date: March, 22 , 2022  
// Last Update: March, 23 , 2022  
// Problem statement: Complex
#include "Complex.h"

Complex::Complex()
{
	realValue = 0;
	imaginaryValue = 0;
}

Complex::Complex(double r)
{
	realValue = r;
	imaginaryValue = 0;
}

Complex::Complex(double r, double i)
{
	realValue = r;
	imaginaryValue = i;
}

double Complex::real()
{
	return realValue;
}

double Complex::imag()
{
	return imaginaryValue;
}

double Complex::norm()
{
	return sqrt(pow(realValue, 2.0) + pow(imaginaryValue, 2.0));
}

Complex Complex::operator+(Complex c)
{
	Complex result;
	result.realValue = realValue + c.realValue;
	result.imaginaryValue = imaginaryValue + c.imaginaryValue;
	return result;
}

Complex Complex::operator-(Complex c)
{

	Complex result;
	result.realValue = realValue - c.realValue;
	result.imaginaryValue = imaginaryValue - c.imaginaryValue;
	return result;
}

Complex Complex::operator*(Complex c)
{
	Complex result;
	result.realValue = realValue * c.realValue - imaginaryValue * c.imaginaryValue;
	result.imaginaryValue = realValue * c.imaginaryValue + imaginaryValue * c.realValue;
	return result;
}

Complex Complex::operator/(Complex c)
{
	Complex result;
	double _a = this->realValue;
	double _b = this->imaginaryValue;
	double _c = c.realValue;
	double _d = c.imaginaryValue;
	result.realValue = (_a * _c + _b * _d) / (pow(_c, 2.0) + pow(_d, 2.0));
	result.imaginaryValue = (_c * _b - _a * _d) / (pow(_c, 2.0) + pow(_d, 2.0));
	
	return result;
}

double real(Complex c)
{
	return c.real();
}

double imag(Complex c)
{
	return c.imag();
}

double norm(Complex c)
{
	return c.norm();
}

Complex operator+(double d, Complex c)
{
	Complex result(d);
	return result + c;
}

Complex operator-(double d, Complex c)
{
	Complex result(d);
	return result - c;
}

Complex operator*(double d, Complex c)
{
	Complex result(d);
	return result * c;
}

Complex operator/(double d, Complex c)
{
	Complex result(d);
	return result / c;
}

bool operator==(Complex c1, Complex c2)
{
	if (c1.realValue == c2.realValue && c1.imaginaryValue == c2.imaginaryValue) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& strm, const Complex& c)
{
	strm << c.realValue << " + " << c.imaginaryValue << "*i";
	return strm;
	// TODO: 於此處插入傳回陳述式
}

istream& operator>>(istream& strm, Complex& c)
{
	char trash;
	strm >> trash >> trash >> c.realValue >> trash >> c.imaginaryValue >> trash >> trash;
	return strm;
	// TODO: 於此處插入傳回陳述式
}
