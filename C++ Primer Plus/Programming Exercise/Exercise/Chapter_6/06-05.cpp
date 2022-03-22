#include <iostream>

using namespace std;

int main05() {
	double income = 0;
	cout << "income: ";
	while (cin >> income && income >= 0) {
		if (income <= 5000) {
			cout << 0 << endl;;
		}
		else if (income <= 15000) {
			cout << (income - 5000) * 0.1 << endl;
		}
		else if (income <= 35000) {
			cout << 10000 * 0.1 + (income - 15000) * 0.15 << endl;
		}
		else {
			cout << 10000 * 0.1 + 20000 * 0.15 + (income - 35000) * 0.2 << endl;
		}
		cout << "income: ";
	}

	return 0;
}