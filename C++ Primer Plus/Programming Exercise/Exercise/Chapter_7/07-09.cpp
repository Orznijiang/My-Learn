#include <iostream>

using namespace std;

const int SLEN = 30;

struct student {
	char fullname[SLEN];
	char hobby[SLEN];
	int ooplevel;
};

int getinfo(student pa[], int n);
void display1(student st);
void display2(const student* ps);
void display3(const student pa[], int n);

int main09() {
	cout << "Enter class size : ";
	int class_size;
	cin >> class_size;
	while (cin.get() != '\n') {
		continue;
	}

	student* ptr_stu = new student[class_size];
	int entered = getinfo(ptr_stu, class_size);
	for(int i = 0; i < entered; i++) {
		display1(ptr_stu[i]);
		display2(&ptr_stu[i]);
	}
	display3(ptr_stu, entered);
	delete[] ptr_stu;
	cout << "Done\n";

	return 0;
}

int getinfo(student pa[], int n) {
	for (int i = 0; i < n; i++) {
		cout << "Student " << i + 1 << "\n";
		while (1) {
			cout << "fullname : ";
			if (!(cin.getline(pa[i].fullname, SLEN))) {
				cout << "Please enter again.\n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				continue;
			}
			break;
		}
		if (strlen(pa[i].fullname) == 0) {
			return i;
		}
		while (1) {
			cout << "hobby : ";
			if (!(cin.getline(pa[i].hobby, SLEN))) {
				cout << "Please enter again.\n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				continue;
			}
			break;
		}
		while (1) {
			cout << "ooplevel : ";
			if (!(cin >> pa[i].ooplevel)) {
				cout << "Please enter again.\n";
				cin.clear();
				while (cin.get() != '\n')
					continue;
				continue;
			}
			cin.get();
			break;
		}
	}
	return n;
}

void display1(student st) {
	cout << "fullname : " << st.fullname << endl;
	cout << "hobby : " << st.hobby << endl;
	cout << "ooplevel : " << st.ooplevel << endl;
}

void display2(const student* ps) {
	cout << "fullname : " << ps->fullname << endl;
	cout << "hobby : " << ps->hobby << endl;
	cout << "ooplevel : " << ps->ooplevel << endl;
}

void display3(const student pa[], int n) {
	for (int i = 0; i < n; i++) {
		cout << "Sdudent " << i + 1 << endl;
		cout << "fullname : " << pa[i].fullname << endl;
		cout << "hobby : " << pa[i].hobby << endl;
		cout << "ooplevel : " << pa[i].ooplevel << endl;
	}
}