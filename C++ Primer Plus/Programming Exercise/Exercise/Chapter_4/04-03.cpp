#include <iostream>
#include <cstring>

using namespace std;

int main03() {
	const int Arsize = 20;
	char first_name[Arsize];
	char last_name[Arsize];

	cout << "Enter your first name: ";
	cin.getline(first_name, Arsize);
	cout << "Enter your last name: ";
	cin.getline(last_name, Arsize);
	cout << "Here's the information in a single string: " << last_name << ", " << first_name << endl;

	return 0;
}