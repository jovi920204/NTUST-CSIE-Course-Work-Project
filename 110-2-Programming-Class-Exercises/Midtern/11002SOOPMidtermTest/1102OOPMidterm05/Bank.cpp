#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Bank.h"


Bank::Bank()
{
	this->balance = 0;
	this->debt = 0;
	this->bill = 0;
	this->isLate = 0;
	this->creditscore = 200;
}

//TODO
void Bank::deposit(int newBalance)
{
	balance += newBalance;
}

//TODO
void Bank::loan(double newDebt)
{
	int maxNum = 0;
	if (150 < creditscore <= 200) {
		maxNum = balance * 5;
	}
	else if (100 < creditscore <= 150) {
		maxNum = balance * 3;
	}
	else if (50 < creditscore <= 100) {
		maxNum = balance * 2;
	}
	else if (20 < creditscore <= 50) {
		maxNum = balance;
	}
	else if (creditscore <= 20) {
		maxNum = 0;
	}
	if(newDebt > maxNum)
		debt += maxNum;
	else
		debt += newDebt;
}


//TODO
double Bank::getBalance()
{
	return balance;
}

//TODO
double Bank::getDebt()
{
	return debt;
}

//TODO
void Bank::payMonthlyBill()
{
	if (balance >= debt)
	{
		balance -= debt;
		debt = 0;
		creditscore += 50;
		debt *= 1.01f;
	}
	else if (balance >= debt / 2)
	{
		balance -= debt / 2;
		debt -= debt / 2;
		creditscore += 20;
		debt *= 1.01f;
	}
	else if (balance >= debt / 10)
	{
		balance -= debt / 10;
		debt -= debt / 10;
		creditscore += 20;
		debt *= 1.01f;
	}
	else if (balance >= debt / 10)
	{
		balance -= debt / 10;
		debt -= debt / 10;
		creditscore -= 30;
		debt *= 1.01f;
	}
	else
	{
		debt -= balance;
		balance -= 0;
		creditscore -= 100;
		debt *= 1.01f;
		debt += 300;
	}

	if (creditscore > 200)
		creditscore = 200;
	else if (creditscore < 0)
		creditscore = 0;
}

//OPTIONAL, WILL NOT BE CALLED BY MAIN
double Bank::setMaxloan()
{
	return 0;
}