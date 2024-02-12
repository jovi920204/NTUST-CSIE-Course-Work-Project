#include "BigNumber.h"

#pragma region operator==
bool operator==(const BigNumber& a, const BigNumber& b)
{
	if (a.sign != b.sign)
		return false;
	if (a.numerator != b.numerator)
		return false;
	if (a.denominator != b.denominator)
		return false;
	return true;
}

bool operator==(const BigNumber& a, const int& intB)
{
	return a == BigNumber(intB);
}

bool operator==(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) == b;
}
#pragma endregion

#pragma region operator!=
bool operator!=(const BigNumber& a, const BigNumber& b)
{
	return !(a == b);
}

bool operator!=(const BigNumber& a, const int& intB)
{
	return a != BigNumber(intB);
}

bool operator!=(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) != b;
}
#pragma endregion

#pragma region operator>
bool operator>(const BigNumber& a, const BigNumber& b)
{
	bool flag = a.sign ^ b.sign;
	if (flag)
	{
		if (b.sign)	// a(+), b(-)
			return true;
		else		// a(-), b(+)
			return false;
	}
	// a and b are the same type (++, --)
	flag = a.sign;	// + or -
	int aSize = a.numerator.size(), bSize = b.numerator.size();
	if (aSize != bSize)
		return (aSize > bSize) ^ flag;
	for (int i = 0; i < aSize; i++)
	{
		if (a.numerator[i] != b.numerator[i])
			return (a.numerator[i] > b.numerator[i]) ^ flag;
	}
	return false;
}

bool operator>(const BigNumber& a, const int& intB)
{
	return a > BigNumber(intB);
}

bool operator>(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) > b;
}
#pragma endregion

#pragma region operator>=
bool operator>=(const BigNumber& a, const BigNumber& b)
{
	return a > b || a == b;
}

bool operator>=(const BigNumber& a, const int& intB)
{
	return a >= BigNumber(intB);
}

bool operator>=(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) >= b;
}
#pragma endregion

#pragma region operator<
bool operator<(const BigNumber& a, const BigNumber& b)
{
	return !(a > b || a == b);
}

bool operator<(const BigNumber& a, const int& intB)
{
	return a < BigNumber(intB);
}

bool operator<(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) < b;
}
#pragma endregion

#pragma region operator<=
bool operator<=(const BigNumber& a, const BigNumber& b)
{
	return !(a > b);
}

bool operator<=(const BigNumber& a, const int& intB)
{
	return a <= BigNumber(intB);
}

bool operator<=(const int& intA, const BigNumber& b)
{
	return BigNumber(intA) <= b;
}
#pragma endregion