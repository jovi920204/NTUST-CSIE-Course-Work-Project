// Name: ±i∫Õ≈Ô
// Date: May, 26 , 2022  
// Last Update: May , 26 , 2022  
// Problem statement: Template Binary Search
#pragma once
// use template and typename T
template <typename T>
void ItrBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	// r is last index in array of a
	// l is first index in array of a

	int r = last, l = first;
	int mid;
	while (l <= r) {
		mid = (r + l) / 2;
		if (a[mid] > key) {
			r = mid - 1;
		}
		else if (a[mid] < key) {
			l = mid + 1;
		}
		else {
			found = 1;
			location = mid;
			return;
		}
	}
	found = 0;
	return;
}

template <typename T>
void RecBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	// mid is the average number in first and last
	if (first > last) {
		found = 0;
		return;
	}
	int mid = (first + last + 1) / 2;
	
	if (key < a[mid]) {
		RecBinarySearch(a, first, mid - 1, key, found, location);
	}
	else if (key > a[mid]){
		RecBinarySearch(a, mid + 1, last, key, found, location);
	}
	else {
		found = 1;
		location = mid;
	}
	return;
}