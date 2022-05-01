#include <iostream>

using namespace std;

template <typename T>
T max5(T*);

int main05() {
	int nums1[5]{ 1,3,5,7,9 };
	double nums2[5]{ 2.0, 4.0, 6.0, 8.0, 10.0 };
	cout << "max int : " << max5(nums1) << endl;
	cout << "max double : " << max5(nums2) << endl;

	return 0;
}

template <typename T>
T max5(T* nums) {
	T max = nums[0];
	for (int i = 1; i < 5; i++) {
		if (nums[i] > max)
			max = nums[i];
	}
	return max;
}