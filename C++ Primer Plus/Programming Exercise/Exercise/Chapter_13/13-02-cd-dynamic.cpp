#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "13-02-cd-dynamic.h"

Cd_dynamic::Cd_dynamic(const char* s1, const char* s2, int n, double x) : selections(n), playtime(x) {
	int length = strlen(s1);
	performers = new char[length + 1.0];
	strcpy(performers, s1);
	length = strlen(s2);
	label = new char[length + 1.0];
	strcpy(label, s2);
}

Cd_dynamic::Cd_dynamic(const Cd_dynamic& d) {
	int length = strlen(d.performers);
	performers = new char[length + 1.0];
	strcpy(performers, d.performers);
	length = strlen(d.label);
	label = new char[length + 1.0];
	strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd_dynamic::Cd_dynamic() {
	performers = new char[1];
	performers[0] = '\0';
	label = new char[1];
	label[0] = '\0';
	selections = 0;
	playtime = 0;
}

Cd_dynamic::~Cd_dynamic() {
	delete[] performers;
	delete[] label;
}

void Cd_dynamic::Report() const {
	std::cout << "performers: " << performers << std::endl;
	std::cout << "label: " << label << std::endl;
	std::cout << "selections: " << selections << std::endl;
	std::cout << "playtime: " << playtime << std::endl;
}

Cd_dynamic& Cd_dynamic::operator=(const Cd_dynamic& d) {
	if (this == &d) {
		return *this;
	}
	int length = strlen(d.performers);
	delete[] performers;
	performers = new char[length + 1.0];
	strcpy(performers, d.performers);
	length = strlen(d.label);
	delete[] label;
	label = new char[length + 1];
	strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
	return *this;
}