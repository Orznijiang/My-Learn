// usetime.cpp -- using the fourth fraft of the Time class
// compile usetime.cpp and mytime.cpp together
#include <iostream>
#include "11-04-mytime.h"

int main() {
	using std::cout;
	using std::endl;
	Time aida(3, 35);
	Time tosca(2, 48);
	Time temp;

	cout << "Aida and Tosca:\n";
	cout << aida << "; " << tosca << endl;
	temp = aida + tosca; // operator+()
	cout << "Aida + Tosca: " << temp << endl;
	temp = aida * 1.17; // member operator*()
	cout << "Aida * 1.17: " << temp << endl;
	cout << "10.0 * Tosca: " << 10.0 * tosca << endl;

	return 0;
}