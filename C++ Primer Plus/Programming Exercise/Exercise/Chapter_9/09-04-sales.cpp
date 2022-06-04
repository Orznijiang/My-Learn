#include <iostream>
#include "09-04-sales.h"
namespace SALES {
	void setSales(Sales& s, const double ar[], int n) {
		s.average = 0;
		s.max = ar[0];
		s.min = ar[0];
		for (int i = 0; i < QUARTERS; i++) {
			if (i < n) {
				s.sales[i] = ar[i];
				s.average += ar[i];
				if (ar[i] > s.max) {
					s.max = ar[i];
				}
				if (ar[i] < s.min) {
					s.min = ar[i];
				}
			}
			else {
				s.sales[i] = 0;
			}
		}
		s.average /= n;
	}

	void setSales(Sales& s) {
		for (int i = 0; i < QUARTERS; i++) {
			std::cout << "enter in sale number " << i + 1 << ": ";
			std::cin >> s.sales[i];
		}
		setSales(s, s.sales, QUARTERS);
	}

	void showSales(const Sales& s) {
		std::cout << "---SALES---" << std::endl;
		for (int i = 0; i < QUARTERS; i++) {
			std::cout << "sale " << i + 1 << ": " << s.sales[i] << std::endl;
		}
		std::cout << "average: " << s.average << std::endl;
		std::cout << "max: " << s.max << std::endl;
		std::cout << "min: " << s.min << std::endl;
	}
}