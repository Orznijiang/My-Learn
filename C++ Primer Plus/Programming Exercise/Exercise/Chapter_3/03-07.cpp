#include <iostream>

using namespace std;

int main07() {
	const double _100km2mile = 62.14;
	const double calon2liter = 3.785;
	double cost;
	cout << "Enter the cost of gas per 100km for liter : ";
	cin >> cost;
	cout << int(_100km2mile / (cost / calon2liter) + 0.5) << "mpg" << endl;
	return 0;
}