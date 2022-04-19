#include <iostream>

using namespace std;

const int Seasons{ 4 };
const char* const Snames[Seasons]{ "Spring", "Summer", "Fall", "Winter" };

struct Expense {
	double expenses[Seasons];
};

void fill(Expense*, int);
void show(Expense*, int);

int main08b() {
	Expense expenses;
	fill(&expenses, Seasons);
	show(&expenses, Seasons);

	return 0;
}

void fill(Expense* p, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter " << Snames[i] << " expenses : ";
		cin >> (*p).expenses[i];
	}
}

void show(Expense* p, int size) {
	double total = 0.0;
	cout << "\nEXPENSES\n";
	for (int i = 0; i < size; i++) {
		cout << Snames[i] << " : $" << (*p).expenses[i] << endl;
		total += (*p).expenses[i];
	}
	cout << "Total Expenses : $" << total << endl;
}