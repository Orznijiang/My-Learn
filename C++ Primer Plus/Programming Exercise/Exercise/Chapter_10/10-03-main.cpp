#include <iostream>
#include "10-03-golf.h"

int main03() {
	golf a[5];
	for (int i = 0; i < 5; i++) {
		if (a[i].setgolf()) {
			a[i].showgolf();
		}
		else {
			break;
		}
	}
	return 0;
}