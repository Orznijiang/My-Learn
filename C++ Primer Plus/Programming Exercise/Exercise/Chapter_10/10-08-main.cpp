#include <iostream>
#include "10-08-list.h"

void output(Item& item);

int main08() {
	List list;
	list.addItem(1);
	list.addItem(5);
	std::cout << "isEmpty: " << list.isEmpty() << std::endl;
	std::cout << "isFull: " << list.isFull() << std::endl;
	list.visit(&output); //output also works
	return 0;
}

void output(Item& item)
{
	std::cout << item << std::endl;
}