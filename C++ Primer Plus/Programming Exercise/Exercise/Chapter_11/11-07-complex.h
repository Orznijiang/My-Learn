#pragma once
#include <iostream>

class Complex
{
private:
	double real;
	double imaginary;
public:
	Complex();
	Complex(double, double);
	~Complex();

	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator*(double n) const;
	Complex operator~() const;

	friend Complex operator*(double n, const Complex& c);
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
	friend std::istream& operator>>(std::istream& is, Complex& c);
};