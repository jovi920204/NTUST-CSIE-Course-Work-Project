#include "BigNumber.h"

std::ostream& operator<<(std::ostream& os, const BigNumber& num)
{
	if (num.sign)
		os << '-';

	std::string output = num.numerator;
	if (!num.isInt && num.denominator != "1")
	{
		output = "";
		std::string Dividend = num.numerator, Divisor = num.denominator;
		if (Divisor.size() > Dividend.size())
		{
			while (Divisor.size() > Dividend.size())
				Dividend = "0" + Dividend;
		}
		Dividend = "0" + Dividend;
		BigNumber BN_Divisor(Divisor);
		std::vector<BigNumber> base_num(11);
		for (size_t i = 0; i <= 10; i++)
			base_num[i] = BN_Divisor * i;

		long index_decimalStart = Dividend.size() - Divisor.size();
		//std::cout << Dividend << '/' << Divisor << '.' << index_decimalStart << '\n';
		//Dividend = "0" + Dividend;
		for (long i = 0; i < index_decimalStart + 100; i++)
		{
			if (i == index_decimalStart)
				output += '.';
			if (i >= index_decimalStart)
				Dividend += '0';

			std::string Dividend_tmp = Dividend.substr(i, Divisor.size() + 1);
			int Dividend_lead = 0, Divisor_lead = 0;
			bool is_bigger_than10 = Divisor.size() > 1;
			Dividend_lead += ((char)Dividend_tmp[0] - '0') * (is_bigger_than10 ? 100 : 10);
			Dividend_lead += ((char)Dividend_tmp[1] - '0') * (is_bigger_than10 ? 10 : 1);
			Dividend_lead += ((char)Dividend_tmp[2] - '0') * (is_bigger_than10 ? 1 : 0);
			Divisor_lead += (int)(Divisor[0] - '0') * (is_bigger_than10 ? 10 : 1);
			Divisor_lead += (int)(Divisor[1] - '0') * (is_bigger_than10 ? 1 : 0);
			int quotient = Dividend_lead / Divisor_lead;
			if (base_num[quotient] > BigNumber(Dividend_tmp))
				quotient -= 1;

			std::string remainder = (base_num[quotient] - BigNumber(Dividend_tmp)).numerator;
			while (remainder.size() < Dividend_tmp.size())
				remainder = "0" + remainder;

			Dividend.replace(i, Dividend_tmp.size(), remainder);
			//if(!(i==0&& quotient==0&& index_decimalStart!=1))
			output += (char)(quotient + '0');
		}
		for (size_t i = 0; i < output.size(); i++)
		{
			if (output[i] == '0' && output[i + 1] != '.')
				output.erase(i, 1);
			else
				break;
		}
	}

	os << output;

#ifdef _DEBUG
	os << '\n' << num.numerator << '\n';
	os << num.denominator << '\n';
	os << "isInt: " << num.isInt << " sign: " << num.sign;
#endif // _DEBUG

	return os;
}

std::istream& operator>>(std::istream& is, BigNumber& num)
{
	std::string inputTemp;
	is >> inputTemp;
	num = BigNumber(inputTemp);
	return is;
}