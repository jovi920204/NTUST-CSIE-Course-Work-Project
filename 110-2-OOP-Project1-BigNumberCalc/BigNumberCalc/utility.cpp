#include "BigNumber.h"

BigNumber basicAdd(const BigNumber& a, const BigNumber& b)
{
	// integer addition (++, +-, -+, --)
	BigNumber result, aTemp(a), bTemp(b);
	result.numerator = "";
	if (aTemp.sign ^ bTemp.sign) // (+,-) or (-,+)
	{
		// if abs(negative num) is greater than the other -> result is negative
		if (aTemp.sign && abs(aTemp) > b || bTemp.sign && abs(bTemp) > a)
			result.sign = true;
		if (abs(aTemp) < abs(bTemp))
			std::swap(aTemp, bTemp);
	}
	else // (+,+) or (-,-)
		result.sign = aTemp.sign;

	int carry(0),
		aIndex = aTemp.numerator.size() - 1,
		bIndex = bTemp.numerator.size() - 1;
	for (int temp; aIndex >= 0 || bIndex >= 0; aIndex--, bIndex--)
	{
		// the index from tail to head 
		temp = carry;
		if (aIndex >= 0)
			temp += aTemp.numerator[aIndex] - '0';
		if (bIndex >= 0)
		{
			if (aTemp.sign ^ bTemp.sign) // (-,+) or (+,-) and the bigger number will be at front
				temp -= bTemp.numerator[bIndex] - '0';
			else // (+,+) or (-,-)
				temp += bTemp.numerator[bIndex] - '0';
		}

		if (temp < 0) // only will happen in a and b are not same type (+,-) or (-,+)
		{
			carry = -1;
			result.numerator = (char)(temp + 10 + '0') + result.numerator;
		}
		else // temp >= 0
		{
			carry = temp / 10;
			result.numerator = (char)((temp % 10) + '0') + result.numerator;
		}
	}
	// if carry have value -> one more digit (99 + 1 = 100)
	if (carry > 0)
		result.numerator = (char)(carry + '0') + result.numerator;

	// remove redundant 'zero'
	int zeroNum(0);
	while (result.numerator.size() > 1 && result.numerator[zeroNum] == '0')
		zeroNum++;
	// if result.numerator's digits are all zero
	if (zeroNum == result.numerator.size())
		result.numerator = "0";
	else
		result.numerator = result.numerator.substr(zeroNum);
	return result;
}

BigNumber basicSub(const BigNumber& a, const BigNumber& b)
{
	// integer substruction
	BigNumber temp(b);
	temp.sign = !temp.sign;
	return (a + temp);
}

BigNumber basicMul(const BigNumber& a, const BigNumber& b)
{
	// integer multipication
	BigNumber result, aTemp(a), bTemp(b);

	// check if either of two numbers is zero
	if (aTemp.numerator == "0" || bTemp.numerator == "0")
		return result;

	result.sign = aTemp.sign ^ bTemp.sign;
	if (aTemp.numerator == "1")
	{
		result.numerator = bTemp.numerator;
		return result;
	}
	else if (bTemp.numerator == "1")
	{
		result.numerator = aTemp.numerator;
		return result;
	}

	int aSize = aTemp.numerator.length(),
		bSize = bTemp.numerator.length(),
		len = aSize + bSize;
	int* value = new int[len]();	// allocate memory and initialize to zero
	for (int i = aSize - 1; i >= 0; i--)
	{
		for (int j = bSize - 1; j >= 0; j--)
		{
			int index = (aSize - 1 - i) + (bSize - 1 - j);
			value[index] += (aTemp.numerator[i] - '0') * (bTemp.numerator[j] - '0');
		}
	}
	for (int i = 0; i < len - 1; i++)
	{
		value[i + 1] += value[i] / 10;
		value[i] = value[i] % 10;
	}

	// statistic how many digits have been used
	int index = len - 1;
	while (value[index] == 0)
		index--;

	// put data into BigNumber 
	for (result.numerator = ""; index >= 0; index--)
		result.numerator += (char)(value[index] + '0');

	delete[] value;
	return result;
}

BigNumber basicDiv(const BigNumber& a, const BigNumber& b)
{
	// integer division
	BigNumber result;
	if (b.numerator == "0")
	{
		std::cout << "Warning: division by zero.\n";
		return result;
	}

	result.sign = a.sign ^ b.sign;
	if (b.numerator == "1")
	{
		result.numerator = a.numerator;
		return result;
	}
	else if (b.numerator == a.numerator)
	{
		result.numerator = "1";
		return result;
	}
	else if (abs(b) > abs(a))
	{
		result.numerator = "0";
		result.sign = false;
		return result;
	}

	BigNumber temp, aTemp(abs(a)), bTemp(abs(b));
	result.numerator = "", temp.numerator = "";
	int index(0);
	for (; temp < bTemp; index++)
		temp.numerator += aTemp.numerator[index];

	int mul(0);
	BigNumber sub;
	for (; bTemp + sub <= temp; sub += bTemp)
		mul++;
	result.numerator += (char)(mul + '0');
	temp -= sub;

	for (int i = index; i < aTemp.numerator.size(); i++)
	{
		if (temp.numerator == "0")
			temp.numerator = aTemp.numerator[i];
		else
			temp.numerator += aTemp.numerator[i];
		mul = 0;
		sub = BigNumber();
		for (; bTemp + sub <= temp; sub += bTemp)
			mul++;
		result.numerator += (char)(mul + '0');
		temp -= sub;
	}
	return result;
}

BigNumber abs(BigNumber num)
{
	num.sign = false;
	return num;
}

BigNumber reciprocal(BigNumber num)
{
	std::string temp = num.numerator;
	num.numerator = num.denominator;
	num.denominator = temp;
	return num;
}

BigNumber gcd(const BigNumber& a, const BigNumber& b)
{
	if (b.numerator == "0")
		return a;
	return gcd(b, a % b);
}

BigNumber lcm(const BigNumber& a, const BigNumber& b)
{
	return (a * b) / gcd(a, b);
}

BigNumber power(const BigNumber& base, const BigNumber& num)
{
	// only for base ^ (0.5 * n) and n is integer
	if (!isValidPower(num))
	{
		std::cout << "Warning: power must be multiple of 0.5.\n";
		return base;
	}

	BigNumber num_int = abs(floatToInt(num));
	bool isNeedRoot = abs(num) - num_int == BigNumber("0.5");
	if (base.sign && isNeedRoot)
	{
		std::cout << "Warning: negative number can't do sqrt.\n";
		return base;
	}

	// Binary Exponentiation
	BigNumber result("1");
	for (BigNumber timesBase(base); num_int != 0; num_int /= 2, timesBase *= timesBase)
	{
		if (num_int % 2 == 1)
			result *= timesBase;
	}

	if (isNeedRoot)
		result = result * root(base);

	if (num.sign)
	{
		std::string temp = result.numerator;
		result.numerator = result.denominator;
		result.denominator = temp;
		if (result.denominator != "1")
			result.isInt = 0;
	}
	return result;
}

BigNumber factorial(const BigNumber& num)
{
	if (!num.isInt)
	{
		std::cout << "Warning: float can't do factorial.\n";
		return BigNumber();
	}
	else if (num.sign)
	{
		std::cout << "Warning: negative integer can't do factorial.\n";
		return BigNumber();
	}
	else if (num.numerator == "0" || num.numerator == "1")
		return BigNumber("1");

	// TODO optimize Big(O)
	BigNumber result("2");
	for (BigNumber i("3"); i <= num; i++)
	{
		result *= i;
	}
	return result;
}

BigNumber intToFloat(BigNumber num)
{
	num.isInt = false;
	return num;
}

BigNumber floatToInt(BigNumber num)
{
	BigNumber temp = BigNumber(num.numerator) / BigNumber(num.denominator);
	temp.sign = num.sign;
	return temp;
}

bool isValidPower(const BigNumber& powerNum)
{
	// only bigger than 0.5
	BigNumber base("0.5");
	//std::cout << (powerNum / base) << '\n';
	if ((powerNum / base).denominator != "1")
		return false;
	return true;
}

void simplifyNum(BigNumber& num)
{
	if (num.isInt)
		return;
	if (num.numerator == num.denominator)
	{
		num.numerator = "1";
		num.denominator = "1";
		return;
	}
	BigNumber numerator(num.numerator), denominator(num.denominator);
	BigNumber GCD = gcd(numerator, denominator);
	num.numerator = (numerator / GCD).numerator;
	num.denominator = (denominator / GCD).numerator;
}

std::string basicRoot(std::string inpNum)
{
	BigNumber rootedNum(0);
	std::string remainder = "";
	std::string result = "";
	if (inpNum.size() % 2 != 0)
		inpNum = '0' + inpNum;

	for (size_t i = 0; i < 100; i++)
		inpNum = inpNum + "00";

	for (int i = 0; i < inpNum.size(); i += 2)
	{
		remainder += inpNum.substr(i, 2);
		BigNumber remainder_num(remainder);

		for (BigNumber i(0); i <= 10; i++)
		{
			//std::cout << ((rootedNum * 10) + i) * i << " , " << remainder_num << " , " << i << '\n';
			if (((rootedNum * 10) + i) * i > remainder_num) 
			{
				remainder_num = remainder_num - (rootedNum * 10 + (i - 1)) * (i - 1);
				rootedNum = rootedNum * 10 + (i - 1) + (i - 1);
				result += (i - 1).numerator;
				break;
			}
		}
		remainder = remainder_num.numerator;
	}
	return result;
}

BigNumber root(const BigNumber& num)
{
	BigNumber rootNum(0);
	rootNum.numerator = basicRoot(num.numerator);
	rootNum.denominator = basicRoot(num.denominator);
	rootNum.isInt = 0;
	return rootNum;
}