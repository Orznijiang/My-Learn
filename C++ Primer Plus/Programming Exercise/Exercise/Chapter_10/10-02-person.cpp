#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "10-02-person.h"

Person::Person(const string& ln, const char* fn)
{
	lname = ln;
	std::strcpy(fname, fn);
}

void Person::Show() const
{
	std::cout << fname << " " << lname << std::endl;
}

void Person::FormalShow() const
{
	std::cout << lname << ", " << fname << std::endl;
}