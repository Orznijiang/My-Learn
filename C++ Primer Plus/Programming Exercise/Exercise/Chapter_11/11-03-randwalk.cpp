// randwalk.cpp -- using the Vector class
// compile with the vect.cpp file
#include <iostream>
#include <cstdlib> // rand(), srand() prototypes
#include <ctime>   // time() prototype
#include <numbers>
#include "11-02-vect.h"
int main03() {
	using namespace std;
	using VECTOR::Vector;
	srand(time(0)); // seed random-number generator
	int N;
	unsigned long top = 0, bottom = ULONG_MAX, total = 0;
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "Enter in the test times: ";
	cin >> N;
	for (int i = 0; i < N; i++) {
		cout << "Enter target distance (q to quit): ";
		cin >> target;

		cout << "Enter step length: ";
		if (!(cin >> dstep))
		{
			break;
		}

		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
		}

		total += steps;
		if (steps > top) {
			top = steps;
		}
		if (steps < bottom) {
			bottom = steps;
		}

		steps = 0;
		result.reset(0.0, 0.0);
		step.reset(0.0, 0.0);
	}
	double average = total / double(N);
	cout << "Top: " << top << endl;
	cout << "Bottom: " << bottom << endl;
	cout << "Average: " << average << endl;

	cout << "Bye!\n";
	cin.clear();
	while (cin.get() != '\n')
		continue;
	return 0;
}