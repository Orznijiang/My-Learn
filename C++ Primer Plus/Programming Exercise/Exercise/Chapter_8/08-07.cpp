#include <iostream>

using namespace std;

template <typename T>
T ShowArray(T arr[], int n);

template <typename T>
T ShowArray(T* arr[], int n);

struct debts {
	char name[50];
	double amount;
};

int main07() {
	int things[6] = { 13,31,103,301,310,130 };
	struct debts mr_E[3] =
	{
		{"Ima Wolfe", 2400.0},
		{"Ura Foxe", 1300.0},
		{"Iby Stout", 1800.0}
	};
	double* pd[3];

	// set pointers to the amount numbers of the structures in mr_E
	for (int i = 0; i < 3; i++) {
		pd[i] = &mr_E[i].amount;
	}

	cout << "Total Mr. E's counts of things:";
	// things is an array of int
	cout << ShowArray(things, 6) << endl; // uses template A
	cout << "Total Mr. E's debts:";
	cout << ShowArray(pd, 3) << endl; // uses template B (more specialized)

	return 0;
}

template <typename T>
T ShowArray(T arr[], int n) {
	cout << "template A\n";
	T total = 0.0;
	for (int i = 0; i < n; i++) {
		total +=arr[i];
	}
	return total;
}

template <typename T>
T ShowArray(T* arr[], int n) {
	cout << "template B\n";
	T total = 0.0;
	for (int i = 0; i < n; i++) {
		total += *arr[i];
	}
	return total;
}