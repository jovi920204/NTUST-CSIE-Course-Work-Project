// Name: ±i∫Õ≈Ô
// Date: March, 15 , 2022  
// Last Update: March, 15 , 2022  
// Problem statement: Hot dog stand
#include "HotDogStand.h"
#include <iostream>

HotDogStand::HotDogStand()
{
	standId = nullptr;
	this->hotDogSellAmount = 0;
}

HotDogStand::HotDogStand(const char* id)
{
	standId = const_cast<char*>(id);
	this->hotDogSellAmount = 0;
}

HotDogStand::HotDogStand(const char* id, int amount)
{
	standId = const_cast<char*>(id);
	this->hotDogSellAmount = amount;
	totalSellAmount += amount;
}


HotDogStand::~HotDogStand()
{
}

void HotDogStand::justSold()
{
	this->hotDogSellAmount++;
	totalSellAmount++;
}

void HotDogStand::print()
{
	std::cout << this->standId << " " << this->hotDogSellAmount << std::endl;
}

int HotDogStand::thisStandSoldAmount()
{
	return this->hotDogSellAmount;
}
int HotDogStand::allStandSoldAmount()
{
	return totalSellAmount;
}

int HotDogStand::totalSellAmount = 0;
