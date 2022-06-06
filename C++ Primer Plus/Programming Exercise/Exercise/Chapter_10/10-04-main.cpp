#include "10-04-sales.h"

int main04() {
	using SALES::Sales;
	Sales n1, n2;
	n1.setSales();
	double temp[3]{ 1,2,3 };
	n2 = Sales(temp, 3);

	n1.showSales();
	n2.showSales();

	return 0;
}