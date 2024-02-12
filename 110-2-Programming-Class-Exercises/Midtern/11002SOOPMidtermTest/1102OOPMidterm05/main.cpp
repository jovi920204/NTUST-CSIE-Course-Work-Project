// main01.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Bank.h"

using namespace std;

int main()
{

    Bank bank = Bank();
    bank.deposit(100);
    bank.loan(150);
    
    printf("Deposit Made: 100  Requested Loan:150\n");
    printf("Check balance: %.3f  ", bank.getBalance());
    printf("Check debt: %.3f\n", bank.getDebt());

    bank.payMonthlyBill();
    printf("New balance: %.3f  ", bank.getBalance());
    printf("New debt: %.3f\n\n", bank.getDebt());

    bank.deposit(100);
    bank.loan(1500);
    printf("Deposit Made: 100  Requested Loan:1500\n");
    printf("Check balance: %.3f  ", bank.getBalance());
    printf("Check debt: %.3f\n", bank.getDebt());

    bank.payMonthlyBill();
    printf("New balance: %.3f  ", bank.getBalance()); 
    printf("New debt: %.3f\n\n", bank.getDebt());

    bank.deposit(500);
    bank.loan(2000);
    printf("Deposit Made: 500  Requested Loan:2000\n");
    printf("Check balance: %.3f  ", bank.getBalance());
    printf("Check debt: %.3f\n", bank.getDebt());

    bank.payMonthlyBill();
    printf("New balance: %.3f  ", bank.getBalance());
    printf("New debt: %.3f\n\n", bank.getDebt());

    return 0;
}