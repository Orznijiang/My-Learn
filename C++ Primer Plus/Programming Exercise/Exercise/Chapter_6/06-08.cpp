#include <iostream>
#include <fstream>

using namespace std;

int main08() {
	fstream file;
	file.open("06_08.txt");

	char ch;
	int num = 0;
	while (file.get(ch)) {
		num++;
	}
	cout << num << " characters in this file." << endl;

	file.close();

	return 0;
}