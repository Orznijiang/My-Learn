// stacker.cpp -- testing the Stack class
#include <iostream>
#include <cctype>
#include "10-05-stack.h"

int main05() {
	using namespace std;
	Stack st;
	char ch;
	double total = 0;
	customer cus;
	cout << "Please enter A to add a purchase order,\n" << "P to process a PO, or Q to quit.\n";
	while (cin >> ch && toupper(ch) != 'Q') {
		while (cin.get() != '\n') {
			continue;
		}
		if (!isalpha(ch)) {
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case'A':
		case'a':
			cout << "Enter the customer name to add: ";
			cin.getline(cus.fullname, 35);
			cout << "Enter the customer payment to add: ";
			cin >> cus.payment;
			cin.get();
			if (st.isfull()) {
				cout << "stack already full!\n";
			}
			else {
				st.push(cus);
			}
			break;
		case'P':
		case'p':
			if (st.isempty()) {
				cout << "stack already empty!\n";
			}
			else {
				st.pop(cus);
				total += cus.payment;
				cout << cus.fullname << " poped!\n";
				cout << "payment: " << cus.payment << endl;
				cout << "total: " << total << endl;
			}
			break;
		}
		cout << "Please enter A to add a purchase order,\n" << "P to process a PO, or Q to quit.\n";
	}
	cout << "Bye!\n";
	return 0;
}