#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "09-01-golf.h"

void setgolf(golf& g, const char* name, int hc) {
	strcpy(g.fullname, name);
	handicap(g, hc);
}

int setgolf(golf& g) {
	char name[Len];
	int handicap;
	std::cout << "enter in the name: ";
	std::cin.getline(name, Len - 1);
	std::cout << "enter in the handicap: ";
	std::cin >> handicap;
	std::cin.get();// for \n
	if (strlen(name) != 0) {
		setgolf(g, name, handicap);
		return 1;
	}
	return 0;
}

void handicap(golf& g, int hc) {
	g.handicap = hc;
}

void showgolf(const golf& g) {
	std::cout << "name: " << g.fullname << std::endl;
	std::cout << "handicap: " << g.handicap << std::endl;
}