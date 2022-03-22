#include <iostream>
#include <cctype>

using namespace std;

int main01() {
	char ch;
	while (cin.get(ch) && ch != '@') {
		if (!std::isdigit(ch)) {
			if (std::isupper(ch)) {
				ch = std::tolower(ch);
			}
			else if (std::islower(ch)) {
				ch = std::toupper(ch);
			}
			cout << ch;
		}
	}

	return 0;
}