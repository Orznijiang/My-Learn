#include "12-01-cow.h"

using namespace std;

int main01() {
	Cow c1;
	Cow c2("c2", "eat", 222);
	Cow c3(c2);
	
	c1.showCow();
	c2.showCow();
	c3.showCow();
	c1 = c3;
	c1.showCow();

	return 0;
}