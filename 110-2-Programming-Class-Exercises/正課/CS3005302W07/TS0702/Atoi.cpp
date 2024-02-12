// Name: ±i∫Õ≈Ô
// Date: March, 31 , 2022  
// Last Update: March, 31 , 2022  
// Problem statement: Array to integer
#include "Atoi.h"

Atoi::Atoi()
{
	beTrans = "";
}

Atoi::Atoi(string s)
{
	beTrans = s;
}

void Atoi::SetString(string s)
{
	beTrans = s;
}

const string Atoi::GetString()
{
	return beTrans;
}

int Atoi::Length()
{
	if (beTrans[0] == '-') {
		return beTrans.length() - 1;
	}
	return beTrans.length();
}

bool Atoi::IsDigital()
{
	if (beTrans[0] == '-') {
		for (int i = 1; i < Length(); i++) {
			if (!isdigit(beTrans[i])) {
				return false;
			}
		}
	}
	else {
		for (int i = 0; i < Length(); i++) {
			if (!isdigit(beTrans[i])) {
				return false;
			}
		}
	}
	
	return true;
}

int Atoi::StringToInteger()
{
	int result = 0;
	for (int i = beTrans.length() - 1, base = 1; i >= 0; i--, base *= 10) {
		if (beTrans[i] == '-') {
			result = -result;
		}
		else {
			result += (beTrans[i] - '0') * base;
		}

	}
	return result;
}
