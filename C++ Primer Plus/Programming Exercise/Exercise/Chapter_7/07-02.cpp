#include <iostream>

using namespace std;

int input_grade(double*, int);
void display_grade(double*, int);
double average_grade(double*, int);

int main02() {
	double grades[10];
	int size;
	size = input_grade(grades, 10);
	display_grade(grades, size);
	double average = average_grade(grades, size);
	cout << "average grade : " << average << endl;

	return 0;
}

int input_grade(double* grades, int size) {
	for (int i = 0; i < size; i++) {
		cout << "grade " << i << " : ";
		cin >> grades[i];
		if (grades[i] < 0) {
			return i;
		}
	}
	return size;
}

void display_grade(double* grades, int size) {
	for (int i = 0; i < size; i++) {
		cout << grades[i] << " ";
	}
	cout << "\n";
}

double average_grade(double* grades, int size) {
	double average = 0;
	for (int i = 0; i < size; i++) {
		average += grades[i];
	}
	average /= double(size);
	return average;
}