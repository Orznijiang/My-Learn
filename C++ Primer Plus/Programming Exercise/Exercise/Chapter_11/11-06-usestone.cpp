#include "11-05-stonewt.h"

int main06() {
	Stonewt stones[6]{ {12},{22.1},{3,2} };
	for (int i = 3; i < 6; i++) {
		std::cout << "Enter in pounds: ";
		double pd;
		std::cin >> pd;
		stones[i] = Stonewt(pd);
	}

	Stonewt min_s(INT_MAX), max_s;
	Stonewt test(11, 0);
	int count = 0;
	for (auto n : stones)
	{
		if (n > max_s)
		{
			max_s = n;
		}
		if (n < min_s)
		{
			min_s = n;
		}
		if (n >= test)
		{
			count++;
		}
	}
	std::cout << "max: " << max_s << std::endl;
	std::cout << "min: " << min_s << std::endl;
	std::cout << "above 11 stn: " << count << std::endl;
	return 0;
}