#include <iostream>

using namespace std;

int main02() {
	double nums[10];
	double total = 0;
	int i = 0;
	while (i < 10 && cin >> nums[i]) {
		total += nums[i];
		i++;
	}
	double average = total / i;
	int bigger_num = 0;
	for (int j = 0; j < i; j++) {
		if (nums[j] > average) {
			bigger_num++;
		}
	}
	cout << "average : " << average << endl;
	cout << bigger_num << " numbers bigger than average." << endl;

	return 0;
}