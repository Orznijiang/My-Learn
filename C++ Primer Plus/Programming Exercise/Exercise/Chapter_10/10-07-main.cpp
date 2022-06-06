#include "10-07-plorg.h"

int main07() {
	Plorg plorg1;
	plorg1.report();
	Plorg plorg2{ "sb", 99 };
	plorg2.report();
	plorg2.setCI(100);
	plorg2.report();

	return 0;
}