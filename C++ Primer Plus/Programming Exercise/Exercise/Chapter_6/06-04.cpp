#include <iostream>

using namespace std;

const int strsize = 20;
// Benevolent Order of Programmers name structer
struct bop
{
	char fullname[strsize]; // real name
	char title[strsize];	// job title
	char bopname[strsize];  // secret BOP name
	int preference;			// 0 = fullname, 1 = title, 2 = bopname
};

int main04() {
	const int mem_num = 5;
	bop members[mem_num] = {
		{"Wimp Macho", "sb", "van", 0},
		{"Raki Rhodes", "Junior Programmer", "van", 1},
		{"Celia Laiter", "sb", "MIPS", 2},
		{"Hoppy Hipman", "Analyst Trainee", "van", 1},
		{"Pat Hand", "sb", "LOOPY", 2}
	};
	cout << "Benevolent Order of Programmers report\n"
		<< "a. display by name	  b. display by title\n"
		<< "c. display by bopname d. display by preference\n"
		<< "q. quit\n";
	char choice;
	cout << "Enter your choice: ";
	while (cin.get(choice) && choice != 'q') {
		switch (choice)
		{
		case 'a':
			for (int i = 0; i < mem_num; i++) {
				cout << members[i].fullname << endl;
			}
			break;
		case 'b':
			for (int i = 0; i < mem_num; i++) {
				cout << members[i].title << endl;
			}
			break;
		case 'c':
			for (int i = 0; i < mem_num; i++) {
				cout << members[i].bopname << endl;
			}
			break;
		case 'd':
			for (int i = 0; i < mem_num; i++) {
				switch (members[i].preference)
				{
				case 0:
					cout << members[i].fullname << endl;
					break;
				case 1:
					cout << members[i].title << endl;
					break;
				case 2:
					cout << members[i].bopname << endl;
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
		cin.get();
		cout << "Next choice: ";
	}
	cout << "Bye!" << endl;

	return 0;
}