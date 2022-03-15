#include <iostream>

using namespace std;

int main06() {
	const int arrSizeYear = 3;
	const int arrSizeMonth = 12;
	const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	int sellNum[3][12]{};
	int total[4]{};
	for (int i = 0; i < arrSizeYear; i++) {
		for (int j = 0; j < arrSizeMonth; j++) {
			cout << "year : " << i + 1 << ", " << months[j] << " : ";
			cin >> sellNum[i][j];
			total[i] += sellNum[i][j];
			total[3] += sellNum[i][j];
		}	
	}
	cout << "year : 1, sell num : " << total[0] << endl;
	cout << "year : 2, sell num : " << total[1] << endl;
	cout << "year : 3, sell num : " << total[2] << endl;
	cout << "total sell num : " << total[3] << endl;

	return 0;
}