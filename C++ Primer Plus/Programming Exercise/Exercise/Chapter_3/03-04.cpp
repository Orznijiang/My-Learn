#include <iostream>

using namespace std;

int main04() {
	const int day2hour = 24;
	const int hour2minute = 60;
	const int minute2second = 60;
	int day, hour, minute, second;
	cout << "Enter the number of seconds: ";
	cin >> second;
	cout << second << " seconds = "
		<< second / minute2second / hour2minute / day2hour << " days, "
		<< second / minute2second / hour2minute % day2hour << " hours, "
		<< second / minute2second % hour2minute << " minutes, "
		<< second % minute2second << " seconds" << endl;
	return 0;
}