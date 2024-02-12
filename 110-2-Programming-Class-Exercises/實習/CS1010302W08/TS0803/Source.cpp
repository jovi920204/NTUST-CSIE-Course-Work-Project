// Name: ±i∫Õ≈Ô
// Date: April, 7 , 2022  
// Last Update: April, 7 , 2022  
// Problem statement: Memory Simulator
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int N, n;
	cin >> N;
	cin >> n;
	vector<unsigned char> memory(N,0);
	for (int i = 0; i < n; i++) {
		string operate;
		int position;
		string type;
		cin >> operate >> position >> type;
		if (operate == "Set") {
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
		else if (operate == "Get") {
			if (position >= N || position < 0) {
				cout << "Violation Access." << endl;
			}
			else {
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
				else if (type == "short") {
					if (position + 1 >= N) {
						cout << "Violation Access." << endl;
					}
					else {
						unsigned int output = 0;
						for (int i = position, base = 1; i < position+2; i++, base <<= 8) {
							output += (int)memory[i] * base;
						}
						cout << output << endl;
					}
				}
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
		else {
		cout << "QQ" << endl;
}
	}
	return 0;
}