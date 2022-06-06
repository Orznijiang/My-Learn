#pragma once

typedef int Item;

class List
{
private:
	enum { MAX = 10 };
	Item items[MAX];
	int back;
public:
	List();
	bool addItem(const Item& item);
	bool isEmpty() const;
	bool isFull() const;
	void visit(void (*pf)(Item&));
};