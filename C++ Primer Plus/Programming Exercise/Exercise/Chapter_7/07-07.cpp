#include <iostream>

using namespace std;

const int Max = 5;

double* fill_array(double*, double*);
void show_array(const double*, const double*);
void revalue(double*, double*, double r);

int main07() {
	double properties[Max];

	double* end = fill_array(properties, properties + Max);
	if (end != properties) {
		cout << "Enter revaluation factor : ";
		double factor;
		while (!(cin >> factor)) {
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
			cout << "Bad input; Please enter a number.\n";
		}
		revalue(properties, end, factor);
		show_array(properties, end);
	}
	cout << "Done.\n";

	return 0;
}

double* fill_array(double* begin, double* end) {
	for (double* p = begin; p != end; p++) {
		cout << "Enter value # " << int(p - begin) + 1 << " : ";
		if (!(cin >> *p)) {
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
			cout << "Bad input; input process terminated.\n";
			return p;
		}
		else if ((*p) < 0) {
			return p;
		}
	}
	return end;
}

void show_array(const double* begin, const double* end) {
	for (const double* p = begin; p != end; p++) {
		cout << "Property # " << int(p - begin) + 1 << " : ";
		cout << (*p) << endl;
	}
}

void revalue(double* begin, double* end, double r) {
	for (double* p = begin; p != end; p++) {
		(*p) *= r;
	}
}