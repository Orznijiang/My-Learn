#include <iostream>

using namespace std;

int main04(){
	const float cash = 100;
	float daphne = 100;
	float cleo = 100;
	int year = 0;
	do {
		daphne += 0.1 * cash;
		cleo += 0.05 * cleo;
		year++;
	} while (daphne > cleo);

	cout << "year : " << year << endl;
	cout << "Daphne : " << daphne << endl;
	cout << "Cleo : " << cleo << endl;
	
	return 0;
}