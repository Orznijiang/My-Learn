#include <iostream>
#include "10-02-person.h"

int main02() {
	Person one;                      // use default constructor
	Person two("Smythecraft");       // use #2 with one default argument
	Person three("Dimwiddy", "Sam"); // use #2, no defaults
	one.Show();
	one.FormalShow();
	two.Show();
	two.FormalShow();
	three.Show();
	three.FormalShow();

	return 0;
}