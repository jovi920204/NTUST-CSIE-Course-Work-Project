#include <iostream>
#include <vector>
using namespace std;
vector<string> table = {
	{"zero"},
	{"one"},
	{"two"},
	{"three"},
	{"four"},
	{"five"},
	{"six"},
	{"seven"},
	{"eight"},
	{"nine"},
	{"ten"},
	{"eleven"},
	{"twelve"},
	{"thirteen"},
	{"fourteen"},
	{"fifteen"},
	{"sixteen"},
	{"seventeen"},
	{"eighteen"},
	{"nineteen"},
	{"twenty"},
	{"plus"}, // + 21
	{"minus"}, // - 22
	{"times"},// * 23
	{"dividedby"}, // / 24
};
int main() {

	int num = 0;
	cin >> num;
	while (num--) {
		vector<int> operation;
		string str, tmp;
		cin >> str;
		for (const auto& val : str) {
			tmp += val;
			for (int i = 0; i < table.size(); i++) {
				if (tmp.find(table[i]) != string::npos) {
					operation.push_back(i);
					tmp = string();
				}
			}
		}
		bool findMulorDiv = false;
		bool findAddorMin = false;
		while (operation.size() > 1) {

			for (int i = 0; i < operation.size(); i++) {
				if (operation[i] == 22) {
					if (i == 0 || (24 >= operation[i - 1] && operation[i - 1] >= 21)) {
						operation[i + 1] *= -1;
						operation[i] = -1;
					}
				}
			}
			
			for (int idx = operation.size() - 1; idx >= 0; idx--) {
				if (operation[idx] == -1)
					operation.erase(operation.begin() + idx);
			}
			for (int i = 0; i < operation.size(); i++) {
				if (operation[i] == 21) {
					if (i == 0 || (24 >= operation[i - 1] && operation[i - 1] >= 21)) {
						operation[i + 1] *= 1;
						operation[i] = -1;
					}
				}
			}
			
			for (int idx = operation.size() - 1; idx >= 0; idx--) {
				if (operation[idx] == -1)
					operation.erase(operation.begin() + idx);
			}
			/*for (const auto& val : operation)
				cout << val << " ";
			cout << "\n";*/

			for (int i = 0; i < operation.size(); i++) {
				if (findAddorMin == false) {
					if (operation[i] == 23) {
						int val1 = operation[i - 1], val2 = operation[i + 1];
						operation[i] = val1 * val2;
						operation.erase(operation.begin() + i + 1);
						operation.erase(operation.begin() + i - 1);
						findMulorDiv = true;
						break;
					}
					else if (operation[i] == 24) {
						int val1 = operation[i - 1], val2 = operation[i + 1];
						operation[i] = val1 / val2;
						operation.erase(operation.begin() + i + 1);
						operation.erase(operation.begin() + i - 1);
						findMulorDiv = true;
						break;
					}
				}
				else {
					if (operation[i] == 21) {
						int val1 = operation[i - 1], val2 = operation[i + 1];
						operation[i] = val1 + val2;
						operation.erase(operation.begin() + i + 1);
						operation.erase(operation.begin() + i - 1);
						break;
					}
					else if (operation[i] == 22) {
						int val1 = operation[i - 1], val2 = operation[i + 1];
						operation[i] = val1 - val2;
						operation.erase(operation.begin() + i + 1);
						operation.erase(operation.begin() + i - 1);
						break;
					}
				}
			}
			if (findMulorDiv == false)
				findAddorMin = true;

			if (findAddorMin == false)
				findMulorDiv = false;

		}
		cout << table[operation.front()] << "\n";
	}
	return 0;
}