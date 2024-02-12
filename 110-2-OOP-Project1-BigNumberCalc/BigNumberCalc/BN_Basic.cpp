#include "BigNumber.h"
#include "FrontEndAnalyze.h"

BigNumber::BigNumber()
{
	// initial value = 0 (int)
	sign = false;
	isInt = true;
	numerator = "0";
	denominator = "1";
}

BigNumber::BigNumber(const std::string num)
{
	// avoid empty string
	if (num.empty())
	{
		sign = false;
		isInt = true;
		numerator = "0";
		denominator = "1";
	}
	else if (isEquation(num))
	{
		*this = convert(format(num));
	}
	else
	{
		sign = false;
		numerator = num;
		if (!isdigit(num[0]))
		{
			sign = (num[0] == '-');
			// remove '-' or '+'
			numerator = numerator.substr(1);
		}
		denominator = "1";

		int pointPosition = numerator.find('.');
		// if could not find '.' -> is int
		isInt = (pointPosition == std::string::npos);
		
		// Warning information about the dot operation is used improper.
		if (num[0] == '.' || num[num.size() - 1] == '.')
		{
			std::cout << "Warning: The number " << num << " is not satisfied with dot format, we ignore the dot." << std::endl;
		}

		// if is float
		if (!isInt)
		{
			// 1. remove '.'
			numerator.erase(pointPosition, 1);
			// 2. denominator should be bigger 
			denominator += std::string(numerator.size() - pointPosition, '0');
		}

		// remove redundant 'zero'
		int zeroNum(0);
		while (numerator.size() > 1 && numerator[zeroNum] == '0')
			zeroNum++;
		// if result.numerator's digits are all zero
		if (zeroNum == numerator.size())
			numerator = "0";
		else
			numerator = numerator.substr(zeroNum);

		if (sign && numerator == "0") // -0
			sign = false;
	}
	
	if (!isInt)
		simplifyNum(*this);
}

BigNumber::BigNumber(const BigNumber& num)
{
	this->numerator = num.numerator;
	this->denominator = num.denominator;
	this->isInt = num.isInt;
	this->sign = num.sign;
}

BigNumber::BigNumber(const short& num)
{
	std::stringstream ss;
	ss << num;
	new (this) BigNumber(ss.str());
}

BigNumber::BigNumber(const int& num)
{
	std::stringstream ss;
	ss << num;
	new (this) BigNumber(ss.str());
}

BigNumber::BigNumber(const long long& num)
{
	std::stringstream ss;
	ss << num;
	new (this) BigNumber(ss.str());
}

BigNumber::BigNumber(const double& num)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(15) << num;
	new (this) BigNumber(ss.str());
}

BigNumber::BigNumber(std::string inputNum, std::string inputDen)
{
	// parse numerator and denominator (+,- integer, float)
	BigNumber numerator(inputNum), denominator(inputDen);
	numerator.isInt = false, denominator.isInt = false;
	*this = numerator / denominator;
}