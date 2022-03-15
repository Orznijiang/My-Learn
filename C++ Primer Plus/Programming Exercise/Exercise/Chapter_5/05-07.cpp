#include <iostream>
#include <string>

using namespace std;

struct Car
{
	string make;
	int year_made;
};

int main07() {
	int num;
	cout << "How many cars do you wish to catalog? ";
	cin >> num;
	cin.get();

	Car* cars = new Car[num];
	for (int i = 0; i < num; i++) {
		cout << "Car #" << i + 1 << ":" << endl;
		cout << "Please enter the make: ";
		getline(cin, cars[i].make);
		cout << "Please enter the year made: ";
		cin >> cars[i].year_made;
		cin.get();
	}
	cout << "Here is your collection:" << endl;
	for (int i = 0; i < num; i++) {
		cout << cars[i].year_made << " " << cars[i].make << endl;
	}

	return 0;
}