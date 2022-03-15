#include <iostream>

using namespace std;

int main05() {
	const int arrSize = 12;
	const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	int sellNum[12]{};
	int total{};
	for (int i = 0; i < arrSize; i++) {
		cout << months[i] << " : ";
		cin >> sellNum[i];
		total += sellNum[i];
	}
	cout << "sell num this year : " << total << endl;

	return 0;
}