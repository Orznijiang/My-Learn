#pragma once
// base class
class Cd_dynamic { // represent a CD disk
private:
	char *performers;
	char *label;
	int selections; // number of selections
	double playtime; // playing time in minutes
public:
	Cd_dynamic(const char* s1, const char* s2, int n, double x);
	Cd_dynamic(const Cd_dynamic& d);
	Cd_dynamic();
	virtual ~Cd_dynamic();
	virtual void Report() const; // report all CD data
	Cd_dynamic& operator=(const Cd_dynamic& d);
};

