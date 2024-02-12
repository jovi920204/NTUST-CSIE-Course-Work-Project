#include "BigNumber.h"

#pragma region operator+
BigNumber operator+(const BigNumber& a, const BigNumber& b)
{
	BigNumber result;
	if (a.isInt && b.isInt) // both are integer
	{
		result = basicAdd(a, b);
	}
	else // at least one of a and b is float 
	{
		BigNumber a1(a.numerator), a2(a.denominator), b1(b.numerator), b2(b.denominator);
		BigNumber c11(a1 * b2), c12(a2 * b1), c2(a2 * b2);
		c11.sign = a.sign;
		c12.sign = b.sign;
		result = c11 + c12;
		result.denominator = c2.numerator;
		result.isInt = 0;
		simplifyNum(result);
	}
	return result;
}

BigNumber operator+(const BigNumber& a, const int& intB)
{
	return a + BigNumber(intB);
}

BigNumber operator+(const int& intA,const BigNumber& b)
{
	return BigNumber(intA) + b;
}
#pragma endregion

#pragma region operator-
BigNumber operator-(const BigNumber& a, const BigNumber& b)
{
	BigNumber result;
	if (a.isInt && b.isInt) // both are integer
	{
		result = basicSub(a, b);
	}
	else // at least one of a and b is float 
	{
		BigNumber a1(a.numerator), a2(a.denominator), b1(b.numerator), b2(b.denominator);
		BigNumber c11(a1 * b2), c12(a2 * b1), c2(a2 * b2);
		c11.sign = a.sign;
		c12.sign = b.sign;
		result = c11 - c12;
		result.denominator = c2.numerator;
		result.isInt = 0;
		simplifyNum(result);
	}
	return result;
}

BigNumber operator-(const BigNumber& a, const int& intB)
{
	return a - BigNumber(intB);
}

BigNumber operator-(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) - b;
}
#pragma endregion

#pragma region operator*
BigNumber operator*(const BigNumber& a, const BigNumber& b)
{
	BigNumber result;
	result.sign = a.sign ^ b.sign;
	if (a.isInt && b.isInt) // both are integer
	{
		result = basicMul(a, b);
	}
	else // at least one of a and b is float 
	{
		BigNumber a1(a.numerator), a2(a.denominator), b1(b.numerator), b2(b.denominator);
		result.numerator = (a1 * b1).numerator;
		result.denominator = (a2 * b2).numerator;
		result.isInt = 0;
		simplifyNum(result);
	}
	return result;
}

BigNumber operator*(const BigNumber& a, const int& intB)
{
	return a * BigNumber(intB);
}

BigNumber operator*(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) * b;
}
#pragma endregion

#pragma region operator/
BigNumber operator/(const BigNumber& a, const BigNumber& b)
{
	BigNumber result;
	result.sign = a.sign ^ b.sign;
	if (a.isInt && b.isInt) // both are integer
	{
		result = basicDiv(a, b);
	}
	else // at least one of a and b is float 
	{
		BigNumber a1(a.numerator), a2(a.denominator), b1(b.numerator), b2(b.denominator);
		result.numerator = (a1 * b2).numerator;
		result.denominator = (a2 * b1).numerator;
		if (result.denominator == "0")
		{
			std::cout << "Warning: division by zero.\n";
			return BigNumber();
		}
		result.isInt = 0;
		simplifyNum(result);
	}
	return result;
}

BigNumber operator/(const BigNumber& a, const int& intB)
{
	return a / BigNumber(intB);
}

BigNumber operator/(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) / b;
}
#pragma endregion

#pragma region operator%
BigNumber operator%(const BigNumber& a, const BigNumber& b)
{
	// !!! integer only !!!
	// suppose a and b are integer
	if (!a.isInt || !b.isInt)
		throw "warning: number must be integer\n";

	BigNumber temp = a / b;
	return (a - (b * temp));
}

BigNumber operator%(const BigNumber& a, const int& intB)
{
	return a % BigNumber(intB);
}

BigNumber operator%(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) % b;
}
#pragma endregion

#pragma region operator++
BigNumber& BigNumber::operator++()
{
	*this = *this + BigNumber("1");
	return *this;
}

BigNumber BigNumber::operator++(int cnt)
{
	BigNumber temp = *this;
	++(*this);
	return temp;
}
#pragma endregion

#pragma region operator--
BigNumber& BigNumber::operator--()
{
	*this = *this - BigNumber("1");
	return *this;
}

BigNumber BigNumber::operator--(int cnt)
{
	BigNumber temp = *this;
	--(*this);
	return temp;
}
#pragma endregion