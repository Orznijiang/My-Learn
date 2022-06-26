#define _CRT_SECURE_NO_WARNINGS
#include "12-01-cow.h"
#include <cstring>
#include <iostream>

Cow::Cow() : name("\0"), weight(0) {
	hobby = new char[1];
	hobby[0] = '\0';
}

Cow::Cow(const char* nm, const char* ho, double wt) {
	strcpy(name, nm);
	int length = strlen(ho);
	hobby = new char[length + 1.0];
	strcpy(hobby, ho);
	weight = wt;
}

Cow::Cow(const Cow& c) {
	strcpy(name, c.name);
	int length = strlen(c.hobby);
	hobby = new char[length + 1.0];
	strcpy(hobby, c.hobby);
	weight = c.weight;
}

Cow::~Cow() {
	delete[] hobby;
}

const Cow& Cow::operator=(const Cow& c)
{
	strcpy(name, c.name);
	delete[] hobby;
	int length = strlen(c.hobby);
	hobby = new char[length + 1.0];
	strcpy(hobby, c.hobby);
	weight = c.weight;
	return *this;
}

void Cow::showCow() const {
	std::cout << "name: " << name << std::endl;
	std::cout << "hobby: " << hobby << std::endl;
	std::cout << "weight: " << weight << std::endl;
}
