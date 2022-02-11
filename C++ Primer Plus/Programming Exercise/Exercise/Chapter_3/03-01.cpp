#include <iostream>

using namespace std;

int main01() {
	const int foot2inch = 12;
	cout << "Enter your height in inch : ___\b\b\b";
	int inch;
	cin >> inch;
	cout << "Your height is " << inch / foot2inch << " foots and " << inch % foot2inch << " inches." << endl;
	return 0;
}