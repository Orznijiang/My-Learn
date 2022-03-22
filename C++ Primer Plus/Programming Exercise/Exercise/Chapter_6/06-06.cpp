#include <iostream>
#include <string>

using namespace std;

struct Patron {
	string name;
	double amount;
};

int main06() {
	int num;
	cout << "number of patrons: ";
	cin >> num;
	cin.get();
	Patron* p = new Patron[num];
	for (int i = 0; i < num; i++) {
		cout << "patron " << i << " name: ";
		getline(cin, p[i].name);
		cout << "patron " << i << " amount: ";
		cin >> p[i].amount;
		cin.get();
	}
	bool flag = false;
	cout << "Grand Patrons" << endl;
	for (int i = 0; i < num; i++) {
		if (p[i].amount > 10000) {
			cout << "name: " << p[i].name << " amount: " << p[i].amount << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "none" << endl;
	}

	flag = false;
	cout << "Patrons" << endl;
	for (int i = 0; i < num; i++) {
		if (p[i].amount < 10000) {
			cout << "name: " << p[i].name << " amount: " << p[i].amount << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "none" << endl;
	}

	return 0;
}