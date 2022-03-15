#include <iostream>
#include <cstring>

using namespace std;

int main08() {
	char word[20];
	int num = 0;
	cout << "Enter words (to stop, type the word done):" << endl;
	do {
		cin >> word;
		num++;
	} while (strcmp(word, "done"));
	num--;

	cout << "You entered a total of " << num << " words." << endl;

	return 0;
}