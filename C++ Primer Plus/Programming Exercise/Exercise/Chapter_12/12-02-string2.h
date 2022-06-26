#pragma once
// string2.h -- fixed and augmented string class definition

#include <iostream>
using std::ostream;
using std::istream;

class String {
private:
	char* str;					  // pointer to string
	int len;					  // length of string
	static int num_strings;		  // number of objects
	static const int CINLIM = 80; // cin input limit
public:
	// constructors and other methods
	String(const char* s);
	String();
	String(const String&);
	~String();
	int length() const { return len; }
	// overloaded operator methods
	String& operator=(const String&);
	String& operator=(const char*);
	char& operator[](int i);
	const char& operator[](int i) const;
	// overloaded opretor friends
	friend bool operator<(const String& st1, const String& st2);
	friend bool operator>(const String& st1, const String& st2);
	friend bool operator==(const String& st1, const String& st2);
	friend ostream& operator<<(ostream& os, const String& st);
	friend istream& operator>>(istream& is, String& st);
	// static function
	static int HowMany();

	// add
	friend String operator+(const String& st1, const String& st2);
	void Stringlow();
	void Stringup();
	int count(const char);
};