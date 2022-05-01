#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct CandyBar
{
	char name[20];
	double weight;
	int heat;
};

void set_candyBar(CandyBar&, const char* name = "Millennium", double weight = 2.85, int heat = 350);
void show_candyBar(const CandyBar&);

int main() {
	CandyBar bar1;
	set_candyBar(bar1);
	CandyBar bar2;
	set_candyBar(bar2, "Da Bai Tu", 2, 30);

	show_candyBar(bar1);
	show_candyBar(bar2);

	return 0;
}

void set_candyBar(CandyBar& candyBar, const char* name, double weight, int heat) {
	strcpy(candyBar.name, name);
	candyBar.weight = weight;
	candyBar.heat = heat;
}

void show_candyBar(const CandyBar& candyBar) {
	cout << "name : " << candyBar.name << endl;
	cout << "weight : " << candyBar.weight << endl;
	cout << "heat : " << candyBar.heat << endl;
}