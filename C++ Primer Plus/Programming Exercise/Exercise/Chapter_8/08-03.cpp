#include <iostream>
#include <string>

using namespace std;

void Convert_Upper(string&);

int main03() {
	string str;
	cout << "Enter a string (q to quit): ";
	while (getline(cin, str)) {
		if (str == "q") {
			cout << "Bye,";
			break;
		}
		Convert_Upper(str);
		cout << str << endl;
		cout << "Next string (q to quit): ";
	}

	return 0;
}

void Convert_Upper(string& str) {
	for (int i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}
}