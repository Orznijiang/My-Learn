#include <iostream>
#include <array>

using namespace std;

int main10() {
	array<float, 3> run;
	cout << "first run: ";
	cin >> run[0];
	cout << "second run: ";
	cin >> run[1];
	cout << "third run: ";
	cin >> run[2];

	float average = (run[0] + run[1] + run[2]) / float(run.size());
	cout << "num: " << run.size() << endl;
	cout << "average grade: " << average << endl;;

	return 0;
}