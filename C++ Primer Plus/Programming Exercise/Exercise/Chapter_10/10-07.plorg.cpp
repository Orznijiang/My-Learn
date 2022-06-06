#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "10-07-plorg.h"

Plorg::Plorg(const char* name, int ci)
{
	std::strcpy(this->name, name);
	this->ci = ci;
}

void Plorg::setCI(int ci)
{
	this->ci = ci;
}

void Plorg::report() const
{
	std::cout << "name: " << this->name << std::endl;
	std::cout << "CI: " << this->ci << std::endl;
}