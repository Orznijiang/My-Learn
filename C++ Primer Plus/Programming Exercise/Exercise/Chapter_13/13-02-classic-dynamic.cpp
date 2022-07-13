#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "13-02-classic-dynamic.h"


Classic_dynamic::Classic_dynamic(const char* s1, const char* s2, const char* s3, int n, double x) :
	Cd_dynamic(s1, s2, n, x) {
	int length = strlen(s3);
	mainWork = new char[length + 1.0];
	strcpy(mainWork, s3);
}

Classic_dynamic::Classic_dynamic(const Classic_dynamic& c) : Cd_dynamic(c) {
	int length = strlen(c.mainWork);
	mainWork = new char[length + 1.0];
	strcpy(mainWork, c.mainWork);
}

Classic_dynamic::Classic_dynamic() : Cd_dynamic() {
	mainWork = new char[1];
	mainWork[0] = '\0';
}

Classic_dynamic::~Classic_dynamic() {
	delete[] mainWork;
}

void Classic_dynamic::Report() const {
	Cd_dynamic::Report();
	std::cout << "mainWork: " << mainWork << std::endl;
}

Classic_dynamic& Classic_dynamic::operator=(const Classic_dynamic& c) {
	if (this == &c) {
		return *this;
	}
	Cd_dynamic::operator=(c);
	int length = strlen(c.mainWork);
	delete[] mainWork;
	mainWork = new char[length + 1.0];
	strcpy(mainWork, c.mainWork);
	return *this;
}