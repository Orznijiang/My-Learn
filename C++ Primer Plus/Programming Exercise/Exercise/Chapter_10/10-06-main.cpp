#include <iostream>
#include "10-06-move.h"

int main06() {
	Move pace1(7.0, 8.0);
	Move pace2{ 2.0, 3.0 };
	Move pace3 = pace1.add(pace2);
	pace1.showmove();
	pace2.showmove();
	pace3.showmove();
	return 0;
}