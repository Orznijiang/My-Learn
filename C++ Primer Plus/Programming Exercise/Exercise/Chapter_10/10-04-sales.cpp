#include <iostream>
#include "10-04-sales.h"
namespace SALES {
	Sales::Sales(const double ar[], int n) {
		average = 0;
		if (ar == nullptr) return;
		max = ar[0];
		min = ar[0];
		for (int i = 0; i < QUARTERS; i++) {
			if (i < n) {
				sales[i] = ar[i];
				average += ar[i];
				if (ar[i] > max) {
					max = ar[i];
				}
				if (ar[i] < min) {
					min = ar[i];
				}
			}
			else {
				sales[i] = 0;
			}
		}
		average /= n;
	}

	void Sales::setSales() {
		for (int i = 0; i < QUARTERS; i++) {
			std::cout << "enter in sale number " << i + 1 << ": ";
			std::cin >> sales[i];
		}
		*this = Sales(sales, QUARTERS);
	}

	void Sales::showSales() const {
		std::cout << "---SALES---" << std::endl;
		for (int i = 0; i < QUARTERS; i++) {
			std::cout << "sale " << i + 1 << ": " << sales[i] << std::endl;
		}
		std::cout << "average: " << average << std::endl;
		std::cout << "max: " << max << std::endl;
		std::cout << "min: " << min << std::endl;
	}
}