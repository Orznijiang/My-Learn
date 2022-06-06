#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "10-03-golf.h"

golf::golf(const char* name, int hc) {
	strcpy(fullname, name);
	handicap(hc);
}

int golf::setgolf() {
	char name[Len];
	int handicap;
	std::cout << "enter in the name: ";
	std::cin.getline(name, Len - 1);
	std::cout << "enter in the handicap: ";
	std::cin >> handicap;
	std::cin.get();// for \n
	if (strlen(name) != 0) {
		*this = golf(name, handicap);
		return 1;
	}
	return 0;
}

void golf::handicap(int hc) {
	cap = hc;
}

void golf::showgolf() const {
	std::cout << "name: " << fullname << std::endl;
	std::cout << "handicap: " << cap << std::endl;
}