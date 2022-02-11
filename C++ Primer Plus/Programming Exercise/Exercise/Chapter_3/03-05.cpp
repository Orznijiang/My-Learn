#include <iostream>

using namespace std;

int main05() {
	long long world, us;
	cout << "Enter the world's population: ";
	cin >> world;
	cout << "Enter the population of the US: ";
	cin >> us;
	cout << "The population of the US is " << double(us) / world * 100 << "% of the world population." << endl;
	return 0;
}