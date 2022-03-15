#include <iostream>
#include <string>

using namespace std;

int main09() {
	string word;
	int num = 0;
	cout << "Enter words (to stop, type the word done):" << endl;
	do {
		cin >> word;
		num++;
	} while (word != "done");
	num--;

	cout << "You entered a total of " << num << " words." << endl;

	return 0;
}