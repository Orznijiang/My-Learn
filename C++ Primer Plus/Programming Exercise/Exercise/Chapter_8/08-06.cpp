#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
T maxn(T*, int);



int main06() {
	int nums1[6]{ 1,2,3,4,5,6 };
	double nums2[4]{ 1.0,2.0,3.0,4.0 };
	const char* strs[5]{ "1","22","333","4444","55555" };
	cout << "max int : " << maxn(nums1, 6) << endl;
	cout << "max double : " << maxn(nums1, 4) << endl;
	cout << "max str : " << maxn(strs, 5) << endl;

	return 0;
}

template <typename T>
T maxn(T* nums, int n) {
	T max = nums[0];
	for (int i = 1; i < n; i++) {
		if (nums[i] > max)
			max = nums[i];
	}
	return max;
}

template <> 
char* maxn(char** strs, int n) {
	int max = strlen(strs[0]);
	int max_index = 0;
	for (int i = 1; i < n; i++) {
		if (strlen(strs[i]) > max) {
			max = strlen(strs[i]);
			max_index = i;
		}
	}
	return strs[max_index];
}