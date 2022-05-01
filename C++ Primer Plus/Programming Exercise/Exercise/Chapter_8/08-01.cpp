#include <iostream>

using namespace std;

void print_str(const char*, int n = 0);

int main01() {
	const char* str = "hello";
	print_str(str);
	cout << endl;
	print_str(str, 0);
	cout << endl;
	print_str(str, 1);

	return 0;
}

void print_str(const char* str, int n) {
	static int flag = 0;
	flag++;
	if (n) {
		for (int i = 0; i < flag; i++) {
			cout << str << endl;
		}
	}
	else {
		cout << str << endl;
	}
}