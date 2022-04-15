#include <iostream>

using namespace std;

float average(float, float);

int main01() {
	float num1, num2;
	do {
		cout << "first num : ";
		cin >> num1;
		if (num1 == 0) break;
		cout << "second num : ";
		cin >> num2;
		if (num2 == 0) break;
		float ave = average(num1, num2);
		cout << "average : " << ave << endl;
	} while (num1 && num2);

	return 0;
}

float average(float num1, float num2) {
	return 2.0 * num1 * num2 / (num1 + num2);
}