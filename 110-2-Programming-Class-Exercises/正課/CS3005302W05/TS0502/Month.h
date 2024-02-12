// Name: ±i∫Õ≈Ô
// Date: March, 15 , 2022  
// Last Update: March, 15 , 2022  
// Problem statement: Design Month Class
#pragma once
class Month
{
public:
	Month();
	Month(char first, char second, char third);
	Month(int monthInt);
	~Month();

	void inputInt();
	void inputStr();
	void outputInt();
	void outputStr();
	Month nextMonth();
private:
	int month;
	char monthStr[4];
};

