#define _CRT_SECURE_NO_WARNINGS
#include "13-04-port.h"
#include <cstring>

// Port
Port::Port(const char* br, const char* st, int b) {
	brand = new char[strlen(br) + 1];
	strcpy(brand, br);
	strncpy(style, st, 19);
	style[19] = '\0';
	bottles = b;
}

Port::Port(const Port& p) {
	brand = new char[strlen(p.brand) + 1];
	strcpy(brand, p.brand);
	strncpy(style, p.style, 19);
	style[19] = '\0';
	bottles = p.bottles;
}

Port& Port::operator=(const Port& p) {
	if (this == &p) {
		return *this;
	}
	delete[] brand;
	brand = new char[strlen(p.brand) + 1];
	strcpy(brand, p.brand);
	strncpy(style, p.style, 19);
	style[19] = '\0';
	bottles = p.bottles;
	return *this;
}

Port& Port::operator+=(int b) {
	bottles += b;
	return *this;
}

Port& Port::operator-=(int b) {
	bottles -= b;
	return *this;
}

void Port::Show() const {
	cout << "brand: " << brand << endl;
	cout << "style: " << style << endl;
	cout << "bottles: " << bottles << endl;
}

ostream& operator<<(ostream& os, const Port& p) {
	os << "brand: " << p.brand << endl;
	os << "style: " << p.style << endl;
	os << "bottles: " << p.bottles << endl;
	return os;
}

// VintagePort
VintagePort::VintagePort() : Port() {
	nickname = new char[5];
	strcpy(nickname, "none");
	year = 0;
}

VintagePort::VintagePort(const char* br, const char* st, int b, const char* nn, int y) : Port(br, st, b) {
	nickname = new char[strlen(nn) + 1];
	strcpy(nickname, nn);
	year = y;
}

VintagePort::VintagePort(const VintagePort& vp) : Port(vp) {
	nickname = new char[strlen(vp.nickname) + 1];
	strcpy(nickname, vp.nickname);
	year = vp.year;
}

VintagePort& VintagePort::operator=(const VintagePort& vp) {
	if (this == &vp) {
		return *this;
	}
	Port::operator=(vp);
	delete[] nickname;
	nickname = new char[strlen(vp.nickname) + 1];
	strcpy(nickname, vp.nickname);
	year = vp.year;
	return *this;
}

void VintagePort::Show() const {
	Port::Show();
	cout << "nickname: " << nickname << endl;
	cout << "year: " << year << endl;
}

ostream& operator<<(ostream& os, const VintagePort& vp) {
	os << (const Port&)vp;
	os << "nickname: " << vp.nickname << endl;
	os << "year: " << vp.year << endl;
	return os;
}