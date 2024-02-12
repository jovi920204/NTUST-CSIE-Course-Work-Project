// Name: ±i∫Õ≈Ô
// Date: March, 22 , 2022  
// Last Update: March, 23 , 2022  
// Problem statement: Prime Number
#pragma once
#include <iostream>
#include <cmath>
class PrimeNumber {
public:
	int value;
	int get();
	PrimeNumber();
	PrimeNumber(int _value);
	PrimeNumber & operator++();
	PrimeNumber operator++(int);
	PrimeNumber & operator--();
	PrimeNumber operator--(int);
	friend bool prime(int);
};