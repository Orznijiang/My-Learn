#include "09-04-sales.h"

int main() {
	using SALES::Sales;
	using SALES::setSales;
	using SALES::showSales;
	Sales n1, n2;
	setSales(n1);
	double temp[3]{ 1,2,3 };
	setSales(n2, temp, 3);

	showSales(n1);
	showSales(n2);

	return 0;
}