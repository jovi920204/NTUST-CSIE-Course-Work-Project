#include <iostream>
#include <vector>
using namespace std;

void rShift(string& str1);
void lShift(string& str1);
void addition(string& str1, string& str2);

int main() {
	int N = 0;
	string data1, data2, ans;
	while (cin >> N) {
		cout << "COWCULATIONS OUTPUT\n";
		while (N--) {
			cin >> data1 >> data2;
			for (int i = 0; i < 3; i++) {
				char op;
				cin >> op;
				switch (op)
				{
				case 'A':
					addition(data1, data2);
					break;
				case 'R':
					rShift(data2);
					break;
				case 'L':
					lShift(data2);
					break;
				default:
					break;
				}
			}
			while (data2.size() < 8) {
				data2.insert(data2.begin(), 'V');
			}
			//cout << "ANS: " << data2 << "\n";
			cin >> ans;
			if (ans == data2) {
				cout << "YES\n";
			}
			else {
				cout << "NO\n";
			}
		}
		cout << "END OF OUTPUT\n";
	}
	return 0;
}

void rShift(string& str1)
{
	str1.insert(str1.begin(), 'V');
	str1.pop_back();
}

void lShift(string& str1)
{
	str1.push_back('V');
}

void addition(string& str1, string& str2)
{
	vector<int> val1, val2, ans;

	reverse(str1.begin(), str1.end());
	for (const auto& val : str1) {
		if (val == 'V') {
			val1.push_back(0);
		}else if (val == 'U') {
			val1.push_back(1);
		}else if (val == 'C') {
			val1.push_back(2);
		}else if (val == 'D') {
			val1.push_back(3);
		}
	}
	reverse(str2.begin(), str2.end());
	for (const auto& val : str2) {
		if (val == 'V') {
			val2.push_back(0);
		}
		else if (val == 'U') {
			val2.push_back(1);
		}
		else if (val == 'C') {
			val2.push_back(2);
		}
		else if (val == 'D') {
			val2.push_back(3);
		}
	}

	int carry = 0;
	for (int i = 0; i < val1.size() || i < val2.size(); i++) {
		int digit = 0;
		
		digit += carry;
		if (i < val1.size()) {
			digit += val1[i];
		}
		if (i < val2.size()) {
			digit += val2[i];
		}
		carry = digit / 4;
		digit %= 4;
		ans.push_back(digit);
	}
	if(carry)
		ans.push_back(carry);
	string tmpStr;
	for (int i = ans.size() - 1; i >= 0; i--) {
		if (ans[i] == 0) {
			tmpStr.push_back('V');
		}else if (ans[i] == 1) {
			tmpStr.push_back('U');
		}else if (ans[i] == 2) {
			tmpStr.push_back('C');
		}else if (ans[i] == 3) {
			tmpStr.push_back('D');
		}
	}
	str2 = tmpStr;
	reverse(str1.begin(), str1.end());
	/*cout << "ADD" << "STR1: " << str1 << "\n";
	cout <<"ADD" << "STR2: " << str2 << "\n";*/
}
