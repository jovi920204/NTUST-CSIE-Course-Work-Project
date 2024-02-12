// Name: ±i∫Õ≈Ô
// Date: March, 10 , 2022  
// Last Update: March, 10 , 2022  
// Problem statement: Fraction
#ifndef Fraction_H
#define Fraction_H
#include <iostream>
#include <iomanip>
using namespace std;

class Fraction
{
private:
	int numerator;
	int denominator;
public:
	void setNumerator(int nu);
	void setDenominator(int de);
	void getDouble();
	void outputReducedFraction();

};

#endif //Fraction_H