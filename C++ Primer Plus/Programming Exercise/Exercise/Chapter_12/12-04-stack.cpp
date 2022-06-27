#include "12-04-stack.h"

Stack::Stack(int n) {
	if (n > MAX) {
		n = 10;
	}
	size = n;
	pitems = new Item[size];
	top = 0;
}

Stack::Stack(const Stack& st) {
	size = st.size;
	top = st.top;
	pitems = new Item[size];
	for (int i = 0; i < top; i++) {
		pitems[i] = st.pitems[i];
	}
}

Stack::~Stack() {
	delete[] pitems;
}

bool Stack::isempty() const {
	return top == 0;
}

bool Stack::isfull() const {
	return top == size;
}

bool Stack::push(const Item& item) {
	if (top < size) {
		pitems[top] = item;
		top++;
		return true;
	}
	else {
		return false;
	}
}

bool Stack::pop(Item& item) {
	if (top > 0) {
		top--;
		item = pitems[top];
		return true;
	}
	else {
		return false;
	}
}

Stack& Stack::operator=(const Stack& st) {
	size = st.size;
	top = st.top;
	delete[] pitems;
	pitems = new Item[size];
	for (int i = 0; i < top; i++) {
		pitems[i] = st.pitems[i];
	}
	return *this;
}