#pragma once


class Bank
{
public:

	Bank();

	void deposit(int newBalance);

	void loan(double newDebt);

	double getBalance();

	double getDebt();

	double setMaxloan();

	void payMonthlyBill();

public:
	double balance;
	double debt;
	double bill;
	int isLate;
	int creditscore;
};