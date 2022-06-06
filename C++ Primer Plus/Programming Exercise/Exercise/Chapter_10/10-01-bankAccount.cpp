#include <iostream>
#include "10-01-bankAccount.h"

BankAccount::BankAccount(const std::string& client, const std::string& num, double bal)
{
	name = client;
	acctnum = num;
	balance = bal;
}

void BankAccount::show() const
{
	std::cout << "name: " << name << std::endl;
	std::cout << "accountName: " << acctnum << std::endl;
	std::cout << "balance: " << balance << std::endl;
}

void BankAccount::deposit(double cash)
{
	balance += cash;
}

void BankAccount::withdraw(double cash)
{
	balance -= cash;
}