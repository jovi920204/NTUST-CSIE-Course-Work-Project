// Name: ±i∫Õ≈Ô
// Date: March, 15 , 2022  
// Last Update: March, 15 , 2022  
// Problem statement: Hot dog stand
#pragma once

class HotDogStand
{
public:
	HotDogStand();
	HotDogStand(const char* id);
	HotDogStand(const char* id, int amount);
	~HotDogStand();
	void justSold();
	void print();
	int thisStandSoldAmount();
	static int allStandSoldAmount();
private:
	char* standId;
	int hotDogSellAmount;
	static int totalSellAmount;
};
