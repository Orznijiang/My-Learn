#include "10-08-list.h"

List::List()
{
	back = 0;
}

bool List::addItem(const Item& item)
{
	if (back < MAX) {
		items[back++] = item;
		return true;
	}
	else {
		return false;
	}
}

bool List::isEmpty() const
{
	return back == 0;
}

bool List::isFull() const
{
	return back == MAX;
}

void List::visit(void (*pf)(Item&))
{
	for (int i = 0; i < back; i++) {
		pf(items[i]);
	}
}