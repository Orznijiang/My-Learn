#include <iostream>

using namespace std;

int main10() {
	int row;
	cout << "Enter in the row number : ";
	cin >> row;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row - i - 1; j++) {
			cout << ".";
		}
		for (int j = 0; j < i + 1; j++) {
			cout << "*";
		}
		cout << endl;
	}

	return 0;
}