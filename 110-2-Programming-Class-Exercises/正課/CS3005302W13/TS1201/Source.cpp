// Name: 張睿麟
// Date: May, 12 , 2022  
// Last Update: May, 12 , 2022  
// Problem statement: Memory Simulator
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int N, n;
	cin >> N;
	cin >> n;
	vector<unsigned char> memory(N, 0);
	
	// 執行次數 n 次
	for (int i = 0; i < n; i++) {
		string operate;
		int position;
		string type;

		// 輸入 "動作" "位置" "型別" 
		cin >> operate >> position >> type;

		// 動作 => "Set"
		if (operate == "Set") {
			// 型別 => "char"
			if (type == "char") {
				if (position >= N) {
					cout << "Violation Access." << endl;
				}
				unsigned long long value;
				cin >> value;
				if (value > 255) {
					value = 255;
				}
				memory[position] = value;
			}
			// 型別 => "short"
			else if (type == "short") {
				if (position + 1 >= N) {
					cout << "Violation Access." << endl;
				}

				unsigned short value;
				cin >> value;
				int index = position;
				while (value > 0 && index < N) {
					memory[index] = value;
					value >>= 8;
					index++;
				}
				if (index < N) {
					memory[index] = '/0';
					index++;
				}
			}
			// 型別 => "int"
			else if (type == "int") {
				if (position + 3 >= N) {
					cout << "Violation Access." << endl;
				}

				unsigned long long value;
				cin >> value;
				int index = position;
				while (value > 0 && index < N) {
					memory[index] = value;
					value >>= 8;
					index++;
				}
				if (index < N) {
					memory[index] = '\0';
					index++;
				}
			}
			// 型別 => "String"
			else if (type == "String") {
				cin.get();
				string value;
				getline(cin, value);
				if (position + value.size() >= N) {
					cout << "Violation Access." << endl;
				}
				int index = position;
				int i = 0;
				while (i < value.size() && index < memory.size()) {
					memory[index] = value[i];
					i++;
					index++;
				}
			}
		}

		// 動作 => "Get"
		else if (operate == "Get") {
			if (position >= N || position < 0) {
				cout << "Violation Access." << endl;
			}
			else {
				// 型別 => "char"
				if (type == "char") {
					if (position >= N) {
						cout << "Violation Access." << endl;
						continue;
					}
					else {
						if (memory[position] > 127) {
							cout << (int)memory[position] << endl;
						}
						else {
							cout << (int)memory[position] << endl;
						}
					}

				}
				// 型別 => "short"
				else if (type == "short") {
					if (position + 1 >= N) {
						cout << "Violation Access." << endl;
					}
					else {
						unsigned int output = 0;
						for (int i = position, base = 1; i < position + 2; i++, base <<= 8) {
							output += (int)memory[i] * base;
						}
						cout << output << endl;
					}
				}
				// 型別 => "int"
				else if (type == "int") {
					if (position + 3 >= N) {
						cout << "Violation Access." << endl;
					}
					else {
						unsigned int output = 0;
						for (int i = position, base = 1; i < position + 4; i++, base <<= 8) {
							output += (int)memory[i] * base;
						}
						cout << output << endl;
					}
				}
				// 型別 => "String"
				else if (type == "String") {
					if (position >= N) {
						cout << "Violation Access." << endl;
						continue;
					}
					else {
						for (int i = position; i < memory.size() && memory[i]; i++) {
							cout << memory[i];
						}
						cout << endl;
					}
				}
			}
		}
	}
	return 0;
}