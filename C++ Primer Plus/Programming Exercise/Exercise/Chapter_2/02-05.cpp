#include <iostream>

using namespace std;

int main05() {
	cout << "Please enter a Celsius value: ";
	float celsius;
	cin >> celsius;
	cout << celsius << " degrees Celsius is " << celsius * 1.8 + 32.0 << " degrees Fahrenheit." << endl;
	return 0;
}