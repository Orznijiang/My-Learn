#include <iostream>

using namespace std;

int Fill_array(double*, int);
void Show_array(double*, int);
void Reverse_array(double*, int);

int main06() {
	double arr[10];
	int size = Fill_array(arr, 10);
	Show_array(arr, size);
	Reverse_array(arr, size);
	Show_array(arr, size);

	return 0;
}

int Fill_array(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << "number " << i << " : ";
		if (!(cin >> arr[i])) {
			cin.clear();
			return i;
		}
	}
	return size;
}

void Show_array(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << "number " << i << " : " << arr[i] << endl;
	}
}

void Reverse_array(double* arr, int size) {
	for (int i = 0, j = size - 1; i < j; i++, j--) {
		double temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
