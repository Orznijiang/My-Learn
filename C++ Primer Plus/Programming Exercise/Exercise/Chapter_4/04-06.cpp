#include <iostream>
#include <string>

using namespace std;

struct CandyBar
{
	string brand;
	float weight;
	int calories;
};

int main06() {
	CandyBar snack[3] = {
		{"Mocha Munch 0", 2.3, 350},
		{"Mocha Munch 1", 2.3, 350},
		{"Mocha Munch 2", 2.3, 350},
	};
	for (int i = 0; i < 3; i++) {
		cout << "brand: " << snack[i].brand << endl;
		cout << "weight: " << snack[i].weight << endl;
		cout << "calories: " << snack[i].calories << endl;
	}

	return 0;
}