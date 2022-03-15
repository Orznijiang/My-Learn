#include <iostream>
#include <array>

using namespace std;

int main02() {
	const int Arsize = 101;
	array<long double, Arsize> factorials;
	factorials[0] = factorials[1] = 1;

	for (int i = 2; i < Arsize; i++) {
		factorials[i] = i * factorials[i - 1];
	}
	for (int i = 0; i < Arsize; i++) {
		cout << i << "! = " << factorials[i] << endl;
	}

	return 0;
}