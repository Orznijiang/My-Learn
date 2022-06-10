#include "11-07-complex.h"

Complex::Complex()
{
	real = imaginary = 0;
}

Complex::Complex(double a, double b)
{
	real = a;
	imaginary = b;
}

Complex::~Complex()
{
}

Complex Complex::operator+(const Complex& c) const
{
	return Complex(real + c.real, imaginary + c.imaginary);
}

Complex Complex::operator-(const Complex& c) const
{
	return Complex(real - c.real, imaginary - c.imaginary);
}

Complex Complex::operator*(const Complex& c) const
{
	return Complex(real * c.real - imaginary * c.imaginary, real * c.imaginary + imaginary * c.real);
}

Complex Complex::operator*(double n) const
{
	return Complex(n * real, n * imaginary);
}

Complex Complex::operator~() const
{
	return Complex(real, -imaginary);
}

Complex operator*(double n, const Complex& c)
{
	return c * n;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << "(" << c.real << "," << c.imaginary << "i)";
	return os;
}

std::istream& operator>>(std::istream& is, Complex& c)
{
	int a;
	std::cout << "real: ";
	is >> c.real;
	std::cout << "imaginary: ";
	is >> c.imaginary;
	return is;
}