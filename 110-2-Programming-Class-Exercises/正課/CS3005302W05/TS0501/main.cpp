// Name: ±i∫Õ≈Ô
// Date: March, 15 , 2022  
// Last Update: March, 15 , 2022  
// Problem statement: Hot dog stand
#include <iostream>
#include "HotDogStand.h"
using namespace std;

int main() {
	HotDogStand stand1("Stand1", 0);
	HotDogStand stand2("Stand2", 100);
	HotDogStand stand3("Stand3");
	stand1.justSold();
	stand2.justSold();
	stand3.justSold();
	stand1.print();
	stand2.print();
	stand3.print();
	std::cout << "Total Sold : " << HotDogStand::allStandSoldAmount() << std::endl;
	return 0;

}