// Name: �i����
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
		// ��Xbit
		long long bits = pow(2, ((Y - 1900) / 10 + 2));
		double sum = 0;
		int N = 1;
		// ��X�̤j��N!
		while (sum < bits) {
			sum += log2(N);
			N++;
		}
		// ����|�j�󥻪��ȡA�ҥH�n�ե�
		cout << N - 2 << endl;
	}
	return 0;
}
