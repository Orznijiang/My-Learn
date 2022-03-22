#include <iostream>

using namespace std;

int main03() {
	cout << "Please enter one of the following choices:" << endl;
	cout << "c) carnivore p) pianist" << endl;
	cout << "t) tree g) game" << endl;
	char ch;
	while (cin.get(ch)) {
		switch (ch)
		{
		case 'c':
			cout << "A maple is a carnivore." << endl;
			break;
		case 'p':
			cout << "A maple is a pianist." << endl;
			break;
		case 't':
			cout << "A maple is a tree." << endl;
			break;
		case 'g':
			cout << "A maple is a game." << endl;
			break;
		default:
			cout << "Please enter a c, p, t, or g: ";
			cin.get();
			continue;
		}
		break;
	}

	return 0;
}