#include <iostream>
#include "12-04-stack.h"

using namespace std;

int main04() {
	Stack s1(6);
	cout << "empty: " << s1.isempty() << endl;
	cout << "full: " << s1.isfull() << endl;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	Stack s2(s1);
	Item it;
	s2.pop(it);
	Stack s3;
	s3 = s2;
	s3.push(it);

	while (!s1.isempty()) {
		s1.pop(it);
		cout << it << " ";
	}
	cout << endl;

	while (!s2.isempty()) {
		s2.pop(it);
		cout << it << " ";
	}
	cout << endl;

	while (!s3.isempty()) {
		s3.pop(it);
		cout << it << " ";
	}
	cout << endl;

	return 0;
}