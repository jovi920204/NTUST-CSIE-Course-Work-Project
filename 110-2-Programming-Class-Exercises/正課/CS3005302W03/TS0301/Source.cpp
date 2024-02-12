// Name: �i����
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
	// rbegin()�O���Vmap�����̫�@�Ӥ�����iterator
	// rend()�O���Vmap�����Ĥ@�Ӥ������e����iterator
	for (iter = mp.rbegin(); iter != mp.rend(); iter++) {
		cout << iter->first << "\t" << iter->second << "\n";
	}


	return 0;
}
