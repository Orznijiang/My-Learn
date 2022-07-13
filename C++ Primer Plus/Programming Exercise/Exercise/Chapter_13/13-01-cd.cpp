#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "13-01-cd.h"

Cd::Cd(const char* s1, const char* s2, int n, double x) : selections(n), playtime(x) {
	strcpy(performers, s1);
	strcpy(label, s2);
}

Cd::Cd(const Cd& d) {
	strcpy(performers, d.performers);
	strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd::Cd() {
	strcpy(performers, "");
	strcpy(label, "");
	selections = 0;
	playtime = 0;
}

Cd::~Cd() {}

void Cd::Report() const {
	std::cout << "performers: " << performers << std::endl;
	std::cout << "label: " << label << std::endl;
	std::cout << "selections: " << selections << std::endl;
	std::cout << "playtime: " << playtime << std::endl;
}

Cd& Cd::operator=(const Cd& d) {
	if (this == &d) {
		return *this;
	}
	strcpy(performers, d.performers);
	strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
	return *this;
}