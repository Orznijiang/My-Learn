#include <iostream>
#include <string>

using namespace std;

struct Pizza
{
	string company;
	float diameter;
	float weight;
};

int main07() {
	Pizza pizza;
	cout << "Company: ";
	getline(cin, pizza.company);
	cout << "Diameter: ";
	cin >> pizza.diameter;
	cout << "Weight: ";
	cin >> pizza.weight;

	cout << "Company: " << pizza.company << endl;
	cout << "Diameter: " << pizza.diameter << endl;
	cout << "Weight: " << pizza.weight << endl;

	return 0;
}