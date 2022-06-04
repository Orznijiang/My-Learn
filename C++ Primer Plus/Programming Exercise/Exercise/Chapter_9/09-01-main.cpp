#include <iostream>
#include "09-01-golf.h"

int main01() {
	golf a[5];
	for (int i = 0; i < 5; i++) {
		if (setgolf(a[i])) {
			showgolf(a[i]);
		}
		else {
			break;
		}
	}
	return 0;
}