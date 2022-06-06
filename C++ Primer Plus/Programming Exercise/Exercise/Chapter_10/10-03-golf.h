#pragma once
// golf.h -- for pe10-03.cpp

const int Len = 40;
class golf {
private:
	char fullname[Len];
	int cap;
public:
	// non-interactive version
	// function sets golf structure to provided name, handicap
	// using values passed as arguments to the function
	golf(const char* name = "\0", int hc = 0);

	// interactive version
	// function solicits name and handicap from user
	// and sets the members of g to the values entered
	// returns 1 if name is entered, 0 if name is empty string
	int setgolf();

	// function resets handicap to new value
	void handicap(int hc);

	// function displays contents of golf structure
	void showgolf() const;
};