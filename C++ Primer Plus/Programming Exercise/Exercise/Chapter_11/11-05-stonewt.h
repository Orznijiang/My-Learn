#pragma once
// stonewt.h -- definition for the Stonewt class
#include <iostream>

class Stonewt
{
private:
	enum { Lbs_per_stn = 14 };	  // pounds per stone
	int stone;                    // whole stones
	double pds_left;              // fractional pounds
	double pounds;                // entire weight in pounds
	enum Mode { STN, IPD, FPD };
	Mode mode;
public:							  
	Stonewt(double lbs, Mode m = FPD);          // constructor for double pounds
	Stonewt(int stn, double lbs, Mode m = STN); // constructor for stone, lbs
	Stonewt();					  // default constructor
	~Stonewt();
	//void show_ibs() const;		  // show weight in pounds format
	//void show_stn() const;		  // show weight in stone format
	friend std::ostream& operator<<(std::ostream& os, const Stonewt& s);
	friend Stonewt operator*(double n, const Stonewt& s) { return s * n; };

	Stonewt operator+(const Stonewt& s) const;
	Stonewt operator-(const Stonewt& s) const;
	Stonewt operator*(double n) const;

	// 11-06
	bool operator>(const Stonewt& s) const;
	bool operator>=(const Stonewt& s) const;
	bool operator<(const Stonewt& s) const;
	bool operator<=(const Stonewt& s) const;
	bool operator==(const Stonewt& s) const;
	bool operator!=(const Stonewt& s) const;
};