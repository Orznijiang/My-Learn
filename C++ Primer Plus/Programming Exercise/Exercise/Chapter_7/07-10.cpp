#include <iostream>

using namespace std;

double add(double, double);
double sub(double, double);
double mul(double, double);
double div(double, double);
double calculate(double, double, double (*)(double, double));

int main() {
	// [] > *
	double (*pf[4])(double, double) = { add, sub, mul, div };
	int first{}, second{};
	while (1) {
		cout << "Enter the first number : ";
		while (!(cin >> first)) {
			cout << "Wrong format. Enter again.\n";
			cout << "Enter the first number : ";
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
		}
		cout << "Enter the second number : ";
		while (!(cin >> second)) {
			cout << "Wrong format. Enter again.\n";
			cout << "Enter the second number : ";
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
		}
		for (int i = 0; i < 4; i++) {
			cout << calculate(first, second, pf[i]) << endl;
		}
		cout << "Input -1 to quit, or continue : ";
		while (!(cin >> first)) {
			cout << "Wrong format. Enter again.\n";
			cout << "Enter the first number : ";
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
		}
		if (first == -1) {
			break;
		}
	}

	return 0;
}

double add(double x, double y) {
	cout << "add : ";
	return x + y;
}

double sub(double x, double y) {
	cout << "sub : ";
	return x - y;
}

double mul(double x, double y) {
	cout << "mul : ";
	return x * y;
}

double div(double x, double y) {
	cout << "div : ";
	return x / y;
}

double calculate(double x, double y, double (*p)(double, double)) {
	return p(x, y);
	//return (*p)(x, y);
}