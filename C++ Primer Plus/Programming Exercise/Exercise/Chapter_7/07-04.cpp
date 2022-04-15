#include <iostream>

using namespace std;

long double probability(unsigned numbers, unsigned picks);

int main04() {
	double total1 = 47, choice1 = 5;
	double total2 = 27, choice2 = 1;
	cout << "pick " << choice1 << " numbers in " << total1 << " common numbers.\n";
	cout << "pick " << choice2 << " numbers in " << total2 << " special numbers.\n";
	cout << "you have one chance in " << probability(total1, choice1) * probability(total2, choice2) << " of winnings.\n";

	return 0;
}

long double probability(unsigned numbers, unsigned picks) {
	long double result = 1.0;
	long double n;
	unsigned p;

	for (n = numbers, p = picks; p > 0; n--, p--) {
		result = result * n / p;
	}

	return result;
}