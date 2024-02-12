// Name: 張睿麟
// Date: May, 21 , 2022  
// Last Update: May , 21 , 2022  
// Problem statement: School Inheritance
#include "School.h"

ostream& operator<<(ostream& os, const School school)
{
	os << school.name << "\t" << school.studentAmount << "\t" << school.studentAmountNextYear;
	return os;
}

void School::admissions(double amount)
{
	if (amount < 0) {
		return;
	}
	studentAmount += amount;
}

void School::dropouts(double amount)
{
	if (amount > studentAmount) {
		return;
	}
	this->studentAmount -= amount;
}

void School::transfer(double amount, School& toSchool)
{
	//cout << name << " " << "doing transfer, amount = " << amount << endl;
	if (amount > studentAmount) {
		return;
	}
	this->dropouts(amount);
	toSchool.admissions(amount);
}

void PrivateSchool::admissions(double amount)
{
	if (amount < 0) {
		return;
	}
	studentAmount += amount;
	track = amount;

}

void PrivateSchool::dropouts(double amount)
{
	if (amount > studentAmount) {
		return;
	}
	studentAmount -= amount;
	track -= amount;
	if (track < 0) {
		studentAmountNextYear -= 100;
		track = 0;
	}

}



void PublicSchool::apply_growth()
{
	studentAmountNextYear += growing_rate * studentAmountNextYear;
}

void PublicSchool::dropouts(double amount)
{
	//cout << name << " doing dropouts, amount = " << amount << endl;
	if (amount > studentAmount) {
		// 要退學的人數大於學生人數
		return;
	}
	studentAmount -= amount;
	if (amount >= 100) {
		studentAmountNextYear -= (studentAmountNextYear * 0.05);
		studentAmountNextYear = (int)studentAmountNextYear;
	}

}


