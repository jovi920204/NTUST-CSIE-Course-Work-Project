// Name: ±i∫Õ≈Ô
// Date: March, 22 , 2022  
// Last Update: March, 23 , 2022  
// Problem statement: Prime Number
#include "PrimeNumber.h"

bool prime(int num)
{
	for (int i = 2; i < sqrt(num) + 0.5; i++) {
		if (num % i == 0)return false;
	}
	return true;
}

int PrimeNumber::get()
{
	return value;
}

PrimeNumber::PrimeNumber()
{
	value = 1;
}

PrimeNumber::PrimeNumber(int _value)
{
	value = _value;
}

PrimeNumber& PrimeNumber::operator++() // •˝++
{
	value++;
	while (!prime(value)) {
		value++;
	}
	PrimeNumber result(value);
	return result;
	// TODO: insert return statement here
}

PrimeNumber PrimeNumber::operator++(int) // ´·++
{
	PrimeNumber result(value);
	value++;
	while (!prime(value)) {
		value++;
	}
	return result;
}

PrimeNumber& PrimeNumber::operator--()
{
	value--;
	while (!prime(value)) {
		value--;
	}
	PrimeNumber result(value);
	return result;
	// TODO: insert return statement here
}

PrimeNumber PrimeNumber::operator--(int)
{
	
	PrimeNumber result(value);
	value--;
	while (!prime(value)) {
		value--;
	}
	return result;
}

