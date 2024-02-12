// Name: 張睿麟
// Date: March, 2 , 2022  
// Last Update: March, 2 , 2022  
// Problem statement: Occurrenc Counting
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int input;
	map<int, int> mp;
	map<int, int>::reverse_iterator iter;
	while (cin >> input) {
		mp[input]++;
	}
	cout << "N\tcount\n";
	// rbegin()是指向map中的最後一個元素的iterator
	// rend()是指向map中的第一個元素的前面的iterator
	for (iter = mp.rbegin(); iter != mp.rend(); iter++) {
		cout << iter->first << "\t" << iter->second << "\n";
	}


	return 0;
}
