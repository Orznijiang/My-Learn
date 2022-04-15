#include <iostream>

using namespace std;

struct box {
	char maker[40];
	float height;
	float width;
	float length;
	float volume;
};

void display(box);
void cal_volume(box*);



int main03() {
	box bb{ "haoyugege", 3, 4, 5 };
	cal_volume(&bb);
	display(bb);

	return 0;
}

void display(box b) {
	cout << "maker : " << b.maker << endl;
	cout << "height : " << b.height << endl;
	cout << "width : " << b.width << endl;
	cout << "length : " << b.length << endl;
	cout << "volume : " << b.volume << endl;
}

void cal_volume(box* p) {
	p->volume = p->height * p->width * p->length;
}