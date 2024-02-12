// Name: ±i∫Õ≈Ô
// Date: March, 3 , 2022  
// Last Update: March, 5 , 2022  
// Problem statement: Bank Account
class BankAccount {
private:
	int balance;
	static int total;
public:
	BankAccount();
	BankAccount(int input);
	void withdraw(int output);
	void save(int input);
	int getBalance();
	static int getAllMoneyInBank();
};