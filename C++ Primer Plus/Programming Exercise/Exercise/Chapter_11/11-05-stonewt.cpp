// stonewt.cpp -- Stonewt methods
#include <iostream>
using std::cout;
#include "11-05-stonewt.h"

// construct Stonewt object from double value
Stonewt::Stonewt(double lbs, Mode m)
{
	stone = int(lbs) / Lbs_per_stn; // integer division
	pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
	pounds = lbs;
	mode = m;
}

// construct Stonewt object from stone, double values
Stonewt::Stonewt(int stn, double lbs, Mode m)
{
	stone = stn;
	pds_left = lbs;
	pounds = stn * Lbs_per_stn + lbs;
	mode = m;
}

// default constructor, wt = 0
Stonewt::Stonewt()
{
	stone = pounds = pds_left = 0;
	mode = FPD;
}

// destructor
Stonewt::~Stonewt()
{
}

//// show weight in stones
//void Stonewt::show_stn() const
//{
//	cout << stone << " stone, " << pds_left << " pounds\n";
//}
//
//// show weight in pounds
//void Stonewt::show_ibs() const
//{
//	cout << pounds << " pounds\n";
//}

std::ostream& operator<<(std::ostream& os, const Stonewt& s)
{
	switch (s.mode) {
	case Stonewt::Mode::STN:
		os << s.stone << " stone, " << s.pds_left << " pounds";
		break;
	case Stonewt::Mode::FPD:
		os << s.pounds << " pounds";
		break;
	case Stonewt::Mode::IPD:
		os << int(s.pounds) << " pounds\n";
		break;
	}
	return os;
}

Stonewt Stonewt::operator+(const Stonewt& s) const
{
	return Stonewt(pounds + s.pounds);
}

Stonewt Stonewt::operator-(const Stonewt& s) const
{
	if (pounds < s.pounds) {
		return Stonewt();
	}
	return Stonewt(pounds - s.pounds);
}

Stonewt Stonewt::operator*(double n) const
{
	return Stonewt(n * pounds);
}

// 11-06
bool Stonewt::operator>(const Stonewt& s) const
{
	return pounds > s.pounds;
}

bool Stonewt::operator>=(const Stonewt& s) const
{
	return pounds >= s.pounds;
}

bool Stonewt::operator<(const Stonewt& s) const
{
	return pounds < s.pounds;
}

bool Stonewt::operator<=(const Stonewt& s) const
{
	return pounds <= s.pounds;
}

bool Stonewt::operator==(const Stonewt& s) const
{
	return pounds == s.pounds;
}

bool Stonewt::operator!=(const Stonewt& s) const
{
	return pounds != s.pounds;
}