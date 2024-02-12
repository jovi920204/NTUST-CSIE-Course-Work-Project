// Name: 張睿麟
// Date: Feb, 24 , 2022  
// Last Update: Feb, 24 , 2022  
// Problem statement: Adding Large Numbers
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct BigInt {
	string value;
};

BigInt Add(const BigInt& lhs, const BigInt& rhs) {
	BigInt result;
	string a(lhs.value);
	string b(rhs.value);
	// 從尾巴開始加法，所以要先反轉
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int carry = 0;
	int length = 0;
	// 判斷a還是b的長度較長
	if (a.size() > b.size()) {
		length = a.size();
		// 補零
		b = b + string(length - b.size(), '0');
	}
	else if (a.size() < b.size()) {
		length = b.size();
		// 補零
		a = a + string(length - a.size(), '0');
	}
	else length = a.size();

	result.value.resize(length);
	// 實施加法
	for (int i = 0; i < length; i++) {
		result.value[i] = (a[i] - '0' + b[i] - '0' + carry) % 10 + '0';
		carry = (a[i] - '0' + b[i] - '0' + carry) / 10;
	}
	if (carry != 0) {
		result.value.push_back(carry + '0');
	}
	reverse(result.value.begin(), result.value.end());
	return result;
}
bool checkIsDigit(const string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) return false;
	}
	return true;
}

int main() {
	int n;
	while (cin >> n) {
		while (n--) {
			string str1, str2;
			BigInt a, b;
			cin >> str1 >> str2;
			//先檢查是否為數字
			if (checkIsDigit(str1) && checkIsDigit(str2)) {
				// 把a,b建立好
				a.value.resize(str1.length());
				b.value.resize(str2.length());
				for (int i = 0; i < str1.length(); i++) {
					a.value[i] = str1[i];
				}
				for (int i = 0; i < str2.length(); i++) {
					b.value[i] = str2[i];
				}
				// 計算
				BigInt result = Add(a, b);
				// 輸出
				cout << result.value << endl;
			}
			else {
				cout << "Not a valid number, please try again.\n";
			}
		}
	}
	return 0;
}