#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct stringy {
	char* str; // points to a string
	int ct; // length of string (not counting '\0')
};

// prototype for set(), show() and show() go here
void set(stringy&, char*);
void show(const stringy&, int num = 1);
void show(const char*, int num = 1);

int main04() {
	stringy beany;
	char testing[] = "Reality isn't what it used to be.";

	set(beany, testing); // first argument is a reference,
						// allocates space to hold copy of testing,
						// sets str member of beany to point to the
						// new block, copies testing to new block,
						// and sets ct member of beany
	show(beany); // prints member string once
	show(beany, 2); // prints member string twice
	testing[0] = 'D';
	testing[1] = 'u';
	show(testing); // prints testing string once
	show(testing, 3); // prints testing string thrice
	show("Done!");

	delete[] beany.str;

	return 0;
}

void set(stringy& str1, char* str2) {
	int length = strlen(str2);
	str1.str = new char[length + 1.0];
	strcpy(str1.str, str2);
	str1.ct = length;
}

void show(const stringy& str, int num) {
	for (int i = 0; i < num; i++) {
		cout << str.str << endl;
	}
}

void show(const char* str, int num) {
	for (int i = 0; i < num; i++) {
		cout << str << endl;
	}
}