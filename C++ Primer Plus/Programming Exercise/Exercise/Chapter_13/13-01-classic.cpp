#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "13-01-classic.h"


Classic::Classic(const char* s1, const char* s2, const char* s3, int n, double x) :
	Cd(s1, s2, n, x) {
	strcpy(mainWork, s3);
}

Classic::Classic(const Classic& c) : Cd(c) {
	strcpy(mainWork, c.mainWork);
}

Classic::Classic() : Cd() {
	strcpy(mainWork, "");
}

Classic::~Classic(){}

void Classic::Report() const {
	Cd::Report();
	std::cout << "mainWork: " << mainWork << std::endl;
}

Classic& Classic::operator=(const Classic& c) {
	if (this == &c) {
		return *this;
	}
	Cd::operator=(c);
	strcpy(mainWork, c.mainWork);
	return *this;
}