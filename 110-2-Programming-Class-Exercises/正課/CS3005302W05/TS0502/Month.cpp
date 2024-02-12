// Name: ±i∫Õ≈Ô
// Date: March, 15 , 2022  
// Last Update: March, 15 , 2022  
// Problem statement: Design Month Class
#include "Month.h"
#include <iostream>
#include <map>
using namespace std;

int strToInt(char* monthStr);
Month::Month()
{
	this->month = 1;
}

Month::Month(char first, char second, char third)
{
	this->monthStr[0] = first;
	this->monthStr[1] = second;
	this->monthStr[2] = third;
	this->monthStr[3] = '\0';
	this->month = strToInt(monthStr);
}

Month::Month(int monthInt)
{
	if (monthInt > 12 || monthInt < 1) {
		this->month = 1;
	}
	else {
		month = monthInt;
	}
	
}


Month::~Month()
{
}

void Month::inputInt()
{
	int x;
	cin >> x;
	if (x < 1 || x > 12) {
		month = 1;
	}
	else {
		month = x;
	}
}

void Month::inputStr()
{
	cin >> monthStr[0] >> monthStr[1] >> monthStr[2];
	monthStr[3] = '\0';
	this->month = strToInt(monthStr);

}

void Month::outputInt()
{
	cout << this->month;
}

void Month::outputStr()
{
	switch (month) {
	case 1:
		cout << "Jan";
		break;
	case 2:
		cout << "Feb";
		break;
	case 3:
		cout << "Mar";
		break;
	case 4:
		cout << "Apr";
		break;
	case 5:
		cout << "May";
		break;
	case 6:
		cout << "Jun";
		break;
	case 7:
		cout << "Jul";
		break;
	case 8:
		cout << "Aug";
		break;
	case 9:
		cout << "Sep";
		break;
	case 10:
		cout << "Oct";
		break;
	case 11:
		cout << "Nov";
		break;
	case 12:
		cout << "Dec";
		break;
	default:
		cout << "Jan";
	}
}

Month Month::nextMonth()
{
	if (month > 11) return Month(1);
	return Month(this->month+1);
}

int strToInt(char *month) {
	string mon = month;
	if (mon == "Jan") {
		return 1;
	}
	else if (mon == "Feb") {
		return 2;
	}
	else if (mon == "Mar") {
		return 3;
	}
	else if (mon == "Apr") {
		return 4;
	}
	else if (mon == "May") {
		return 5;
	}
	else if (mon == "Jun") {
		return 6;
	}
	else if (mon == "Jul") {
		return 7;
	}
	else if (mon == "Aug") {
		return 8;
	}
	else if (mon == "Sep") {
		return 9;
	}
	else if (mon == "Oct") {
		return 10;
	}
	else if (mon == "Nov") {
		return 11;
	}
	else if (mon == "Dec") {
		return 12;
	}
	else {
		return 1;
	}
}
