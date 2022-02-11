#include <iostream>

using namespace std;

int main02() {
	int foot, inch;
	float pound;
	const int foot2inch = 12;
	const double inch2meter = 0.0254;
	const float kg2pound = 2.2;
	cout << "Enter your foot : ";
	cin >> foot;
	cout << "Enter your inch : ";
	cin >> inch;
	cout << "Enter your pound : ";
	cin >> pound;
	double meter = (double(foot2inch) * foot + inch) * inch2meter;
	double kilogram = pound / kg2pound;
	double BMI = kilogram / (meter * meter);
	cout << "BMI : " << BMI << endl;
	return 0;
}