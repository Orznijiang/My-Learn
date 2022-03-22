#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Patron {
	string name;
	double amount;
};

int main09() {
	fstream file;
	file.open("06_09.txt");

	int num;
	file >> num;
	file.get();
	Patron* p = new Patron[num];
	for (int i = 0; i < num; i++) {
		getline(file, p[i].name);
		file >> p[i].amount;
		file.get();
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

	file.close();

	return 0;
}