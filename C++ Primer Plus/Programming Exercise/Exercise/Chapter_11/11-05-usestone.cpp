#include "11-05-stonewt.h"

int main05() {
	Stonewt s1(15.6);
	Stonewt s2(2, 2);
	Stonewt s3;
	std::cout << s1 << '\n' << s2 << "\n" << s3 << '\n';
	Stonewt re1 = s1 + s2;
	Stonewt re2 = s1 - s2;
	Stonewt re3 = s2 - s1;
	Stonewt re4 = s1 * 3;
	Stonewt re5 = 3 * s2;
	std::cout << re1 << "\n"
		<< re2 << "\n"
		<< re3 << '\n'
		<< re4 << '\n'
		<< re5 << '\n';
	return 0;
}