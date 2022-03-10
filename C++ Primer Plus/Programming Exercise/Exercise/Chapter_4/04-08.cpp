#include <iostream>
#include <string>

using namespace std;

struct Pizza
{
	string company;
	float diameter;
	float weight;
};

int main08() {
	Pizza* pizza = new Pizza;
	cout << "Diameter: ";
	cin >> pizza->diameter;
	cout << "Company: ";
	cin.get();
	getline(cin, pizza->company);
	cout << "Weight: ";
	cin >> pizza->weight;

	cout << "Company: " << pizza->company << endl;
	cout << "Diameter: " << pizza->diameter << endl;
	cout << "Weight: " << pizza->weight << endl;

	return 0;
}