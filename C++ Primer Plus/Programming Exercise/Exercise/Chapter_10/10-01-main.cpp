#include "10-01-bankAccount.h"

int main01(){
	BankAccount account("van", "van de account", 100);
	account.show();
	account.deposit(1000);
	account.show();
	account.withdraw(20);
	account.show();

	return 0;
}