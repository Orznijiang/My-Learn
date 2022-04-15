#include <iostream>

using namespace std;

long factorial(int);

int main05() {
	int num = 0;
	do {
		cout << "enter a digit to calculate factorial : ";
		if (cin >> num && num >= 0) {
			cout << "result : " << factorial(num) << endl;
		}
		else if (num < 0) {
			break;
		}
		else {
			cout << "wrong format, input again.\n";
			cin.clear();
			cin.get();
			continue;
		}
	} while (num >= 0);

	return 0;
}

long factorial(int n) {
	if (n == 0) {
		return 1;
	}
	return n * factorial(n - 1);
}