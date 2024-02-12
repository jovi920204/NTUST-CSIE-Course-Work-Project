// Name: �i����
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
	// �q���ڶ}�l�[�k�A�ҥH�n������
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int carry = 0;
	int length = 0;
	// �P�_a�٬Ob�����׸���
	if (a.size() > b.size()) {
		length = a.size();
		// �ɹs
		b = b + string(length - b.size(), '0');
	}
	else if (a.size() < b.size()) {
		length = b.size();
		// �ɹs
		a = a + string(length - a.size(), '0');
	}
	else length = a.size();

	result.value.resize(length);
	// ��I�[�k
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
			//���ˬd�O�_���Ʀr
			if (checkIsDigit(str1) && checkIsDigit(str2)) {
				// ��a,b�إߦn
				a.value.resize(str1.length());
				b.value.resize(str2.length());
				for (int i = 0; i < str1.length(); i++) {
					a.value[i] = str1[i];
				}
				for (int i = 0; i < str2.length(); i++) {
					b.value[i] = str2[i];
				}
				// �p��
				BigInt result = Add(a, b);
				// ��X
				cout << result.value << endl;
			}
			else {
				cout << "Not a valid number, please try again.\n";
			}
		}
	}
	return 0;
}