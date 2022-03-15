#include <iostream>

using namespace std;

int main03() {
	int num, total = 0;

	do {
		cin >> num;
		total += num;
		cout << "total : " << total << endl;
	} while (num);

	return 0;
}