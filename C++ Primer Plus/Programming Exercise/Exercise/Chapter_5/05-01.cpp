#include <iostream>

using namespace std;

int main01() {
	int small, big;
	cin >> small >> big;

	int total = 0;
	for (int i = small; i <= big; i++)
	{
		total += i;
	}
	cout << "total : " << total << endl;

	return 0;
}