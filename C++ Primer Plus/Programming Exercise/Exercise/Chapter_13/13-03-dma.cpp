#define _CRT_SECURE_NO_WARNINGS
#include "13-03-dma.h"
#include <cstring>

// ABC methods
ABC::ABC(const char* l, int r) {
	label = new char[std::strlen(l) + 1];
	std::strcpy(label, l);
	rating = r;
}

ABC::ABC(const ABC& rs) {
	label = new char[std::strlen(rs.label) + 1];
	std::strcpy(label, rs.label);
	rating = rs.rating;
}

void ABC::View() const {
	std::cout << "Label: " << label << std::endl;
	std::cout << "Rating: " << rating << std::endl;
}

ABC& ABC::operator=(const ABC& rs)
{
	if (this == &rs) {
		return *this;
	}
	delete[] label;
	label = new char[std::strlen(rs.label) + 1];
	std::strcpy(label, rs.label);
	rating = rs.rating;
	return *this;
}

// baseDMA methods
baseDMA::baseDMA(const char* l, int r) :ABC(l, r){
}

baseDMA::baseDMA(const baseDMA& rs) : ABC(rs) {
}

void baseDMA::View() const {
	ABC::View();
}

// lacksDMA methods
lacksDMA::lacksDMA(const char* c, const char* l, int r) :ABC(l, r) {
	std::strncpy(color, c, COL_LEN - 1);
	color[COL_LEN - 1] = '\0';
}

lacksDMA::lacksDMA(const char* c, const baseDMA& rs) : ABC(rs) {
	std::strncpy(color, c, COL_LEN - 1);
	color[COL_LEN - 1] = '\0';
}

void lacksDMA::View() const {
	ABC::View();
	std::cout << "Color: " << color << std::endl;
}

// hasDMA methods
hasDMA::hasDMA(const char* s, const char* l, int r) :ABC(l, r) {
	style = new char[std::strlen(s) + 1];
	std::strcpy(style, s);
}

hasDMA::hasDMA(const char* s, const baseDMA& rs) : ABC(rs) {
	style = new char[std::strlen(s) + 1];
	std::strcpy(style, s);
}

hasDMA::hasDMA(const hasDMA& hs) : ABC(hs) {
	style = new char[std::strlen(hs.style) + 1];
	std::strcpy(style, hs.style);
}

hasDMA::~hasDMA() {
	delete[] style;
}

hasDMA& hasDMA::operator=(const hasDMA& hs) {
	if (this == &hs) {
		return *this;
	}
	ABC::operator=(hs);
	delete[] style;
	style = new char[std::strlen(hs.style) + 1];
	std::strcpy(style, hs.style);
	return *this;
}

void hasDMA::View() const {
	ABC::View();
	std::cout << "Style: " << style << std::endl;
}