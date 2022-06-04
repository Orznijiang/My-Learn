#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct chaff {
	char dross[20];
	int slag;
};

double arr[50];

int main03() {
	chaff *chaffs = new (arr) chaff[2];
	strcpy(chaffs[0].dross, "sb");
	strcpy(chaffs[1].dross, "nt");
	chaffs[0].slag = 0;
	chaffs[1].slag = 1;
	for (int i = 0; i < 2; i++) {
		cout << i << ": " << chaffs[i].dross << " " << chaffs[i].slag << endl;
	}

	return 0;
}