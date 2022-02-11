#include <iostream>

using namespace std;

int main03() {
	int degree, minute, second;
	const int degree2minute = 60;
	const int minute2second = 60;
	cout << "Enter a latitude in degrees, minutes, and seconds:" << endl;
	cout << "First, enter the degrees: ";
	cin >> degree;
	cout << "Next, enter the minutes of arc: ";
	cin >> minute;
	cout << "Finally, enter the seconds of arc: ";
	cin >> second;
	cout << degree << " degrees, " << minute << " minutes, " << second << " seconds = "
		<< (second / double(minute2second) + minute) / double(degree2minute) + degree << " degrees" << endl;
	return 0;
}