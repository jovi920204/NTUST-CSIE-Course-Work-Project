// Name: ±i∫Õ≈Ô
// Date: March, 17 , 2022  
// Last Update: March, 17 , 2022  
// Problem statement: Student Records
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef struct {
	string firstName;
	string lastName;
	string phone;
} StRec;

vector<StRec> student;
bool _inputError(string firstName, string secondName, string phone);
void _insert(StRec);
void _search(StRec);
void _delete(StRec);
void _print();

int main() {
	string input;
	while (cin >> input) {
		StRec tempStudent;
		if (input == "insert") {
			cin >> tempStudent.firstName >> tempStudent.lastName >> tempStudent.phone;
			if (_inputError(tempStudent.firstName, tempStudent.lastName, tempStudent.phone) == 0) {
				cout << "Input Error" << endl;
				continue;
			}
			_insert(tempStudent);
		}
		else if (input == "search") {
			cin >> tempStudent.firstName >> tempStudent.lastName >> tempStudent.phone;
			if (_inputError(tempStudent.firstName, tempStudent.lastName, tempStudent.phone) == 0) {
				cout << "Input Error" << endl;
				continue;
			}
			_search(tempStudent);
		}
		else if (input == "delete") {
			cin >> tempStudent.firstName >> tempStudent.lastName >> tempStudent.phone;
			if (_inputError(tempStudent.firstName, tempStudent.lastName, tempStudent.phone) == 0) {
				cout << "Input Error" << endl;
				continue;
			}
			_delete(tempStudent);
		}
		else if (input == "print") {
			_print();
		}
	}


	return 0;
}
bool _inputError(string firstName, string lastName, string phone) {
	if (firstName.length() > 25 || lastName.length() > 30 || phone.length() > 15) {
		return 0;
	}
	for (int i = 0; i < phone.length(); i++) {
		if (!isdigit(phone[i])) {
			return 0;
		}
	}
	return 1;
}
void _insert(StRec st) {
	// find
	int record = -1;
	for (int i = 0; i < student.size(); i++) {
		if (st.firstName == student[i].firstName && st.lastName == student[i].lastName && st.phone == student[i].phone) {
			record = i;
			break;
		}
	}
	if (record != -1 || student.size() >= 10) {
		cout << "Insert Error" << endl;
	}
	else {
		student.push_back(st);
	}
}

void _search(StRec st) {
	int record = -1;
	for (int i = 0; i < student.size(); i++) {
		if (st.firstName == student[i].firstName && st.lastName == student[i].lastName && st.phone == student[i].phone) {
			record = i;
			break;
		}
	}
	if (record != -1) {
		cout << record << endl;
	}
	else {
		cout << "Search Error" << endl;
	}
}
void _delete(StRec st) {
	// find
	int record = -1;
	for (int i = 0; i < student.size(); i++) {
		if (st.firstName == student[i].firstName && st.lastName == student[i].lastName && st.phone == student[i].phone) {
			record = i;
			break;
		}
	}
	if (record == -1) {
		cout << "Delete Error" << endl;
	}
	else {
		student.erase(student.begin()+record);
	}
}
void _print() {
	if (student.size() == 0) {
		cout << "Print Error" << endl;
	}
	else {
		for (auto val : student) {
			cout << val.firstName << " " << val.lastName << " " << val.phone << endl;
		}
	}
}