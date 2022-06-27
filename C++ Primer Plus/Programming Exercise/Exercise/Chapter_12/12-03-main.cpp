#include <iostream>
#include "12-03-stock.h"

const int STKS = 4;
int main03() {
	// create an array of initialized objects
	Stock stocks[STKS] = {
		Stock("NanoSmart", 12, 20.0),
		Stock("Boffo Objects", 200, 2.0),
		Stock("Monolithic Obelisks", 130, 3.25),
		Stock("Fleep Enterprice", 60, 6.5),
	};

	std::cout << "Stock holdings:\n";
	int st;
	for (st = 0; st < STKS; st++) {
		//stocks[st].show();
		std::cout << stocks[st];
	}
	// set pointer to first element
	const Stock* top = &stocks[0];
	for (st = 1; st < STKS; st++) {
		top = &top->topval(stocks[st]);
	}
	// now top points to the most valuable holding
	std::cout << "\nMost valuable holding:\n";
	//top -> show();
	std::cout << *top;
	return 0;
}