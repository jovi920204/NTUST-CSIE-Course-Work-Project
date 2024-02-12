// Name: ±i∫Õ≈Ô
// Date: March, 10 , 2022  
// Last Update: March, 10 , 2022  
// Problem statement: Fraction
#include "Fraction.h"
#include <iomanip>
int GCD(int a, int b) {
	if (b) {
		while ((a %= b) && (b %= a));
		return a + b;
	}
}

void Fraction::setNumerator(int nu)
{
	this->numerator = nu;
}

void Fraction::setDenominator(int de)
{
	this->denominator = de;
}

void Fraction::getDouble()
{
	// if nu can divided de excatly
	if (numerator % denominator == 0 ) std::cout << this->numerator / this->denominator << std::endl;
	else {
		std::cout << fixed << setprecision(6) << (double)this->numerator / (double)this->denominator << std::endl;
	}
}

void Fraction::outputReducedFraction()
{
	int nu = this->numerator;
	int de = this->denominator;
	if (nu % de == 0) { // can be divided excatly
		std::cout << nu / de << std::endl;
	}
	else { // use GCD to check is Irreducible fraction or not
		while (GCD(nu, de) != 1) {
			int gcd = GCD(nu, de);
			nu /= gcd;
			de /= gcd;
		}
		if (de == 1) {
			std::cout << nu << std::endl;
		}
		else {
			std::cout << nu << "/" << de << std::endl;
		}
	}
}


