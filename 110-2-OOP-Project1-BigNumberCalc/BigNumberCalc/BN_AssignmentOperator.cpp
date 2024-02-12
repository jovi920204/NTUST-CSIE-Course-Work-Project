#include "BigNumber.h"

#pragma region BigNumber
BigNumber BigNumber::operator=(const BigNumber& num)
{
	this->numerator = num.numerator;
	this->denominator = num.denominator;
	this->isInt = num.isInt;
	this->sign = num.sign;
	return *this;
}

BigNumber BigNumber::operator+=(const BigNumber& num)
{
	*this = (*this) + num;
	return *this;
}

BigNumber BigNumber::operator-=(const BigNumber& num)
{
	*this = (*this) - num;
	return *this;
}

BigNumber BigNumber::operator*=(const BigNumber& num)
{
	*this = (*this) * num;
	return *this;
}

BigNumber BigNumber::operator/=(const BigNumber& num)
{
	*this = (*this) / num;
	return *this;
}

BigNumber BigNumber::operator%=(const BigNumber& num)
{
	*this = (*this) % num;
	return *this;
}

BigNumber BigNumber::operator=(const std::string input)
{
	*this = BigNumber(input);
	return *this;
}
#pragma endregion

#pragma region int
BigNumber BigNumber::operator=(const int& num)
{
	*this = BigNumber(num);
	return *this;
}

BigNumber BigNumber::operator+=(const int& num)
{
	BigNumber temp(num);
	*this = (*this) + temp;
	return *this;
}

BigNumber BigNumber::operator-=(const int& num)
{
	BigNumber temp(num);
	*this = (*this) - temp;
	return *this;
}

BigNumber BigNumber::operator*=(const int& num)
{
	BigNumber temp(num);
	*this = (*this) * temp;
	return *this;
}

BigNumber BigNumber::operator/=(const int& num)
{
	BigNumber temp(num);
	*this = (*this) / temp;
	return *this;
}
BigNumber BigNumber::operator%=(const int& num)
{
	BigNumber temp(num);
	*this = (*this) % temp;
	return *this;
}
#pragma endregion