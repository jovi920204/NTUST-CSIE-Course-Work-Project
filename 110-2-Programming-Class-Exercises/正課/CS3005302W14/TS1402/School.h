// Name: 張睿麟
// Date: May, 21 , 2022  
// Last Update: May , 21 , 2022  
// Problem statement: School Inheritance
#pragma once
#include <iostream>
#include <string>
using namespace std;

class School
{
	// 這裡的變數要記得用protected不然沒有辦法一起使用
protected:
	string name;
	double studentAmount;
	double studentAmountNextYear;
public:
	School() {};
	School(string _name) {
		name = _name;
	};
	School(string _name, double amount) {
		name = _name;
		studentAmount = amount;
		studentAmountNextYear = amount;
	}
	~School() {};
	virtual void admissions(double amount);
	virtual void dropouts(double amount);
	virtual void transfer(double amount, School& toSchool);
	friend ostream& operator<< (ostream& os, const School school);
};

class PrivateSchool : public School 
{
private:
	double track;
public:
	PrivateSchool() {};

	// 衍生繼承School的constructor
	PrivateSchool(string _name, double amount) : School(_name, amount) {};
	~PrivateSchool() {};

	// override父類別的function
	void admissions(double amount) override;
	void dropouts(double amount) override;
};

class PublicSchool : public School
{
private:
	double growing_rate = 0.05;
public:
	PublicSchool() {};

	// 衍生繼承School的constructor
	PublicSchool(string _name, double amount) : School(_name, amount) {};
	~PublicSchool() {};

	void apply_growth();
	// override父類別的function
	void dropouts(double amount) override;
};
