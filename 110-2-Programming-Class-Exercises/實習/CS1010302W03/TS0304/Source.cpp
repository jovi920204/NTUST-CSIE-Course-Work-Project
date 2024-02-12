// Name: 張睿麟
// Date: March, 3 , 2022  
// Last Update: March, 3 , 2022  
// Problem statement: CPU bit growth
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	long long Y;
	while (cin >> Y) {
		// 算出bit
		long long bits = pow(2, ((Y - 1900) / 10 + 2));
		double sum = 0;
		int N = 1;
		// 找出最大的N!
		while (sum < bits) {
			sum += log2(N);
			N++;
		}
		// 找到後會大於本的值，所以要校正
		cout << N - 2 << endl;
	}
	return 0;
}
