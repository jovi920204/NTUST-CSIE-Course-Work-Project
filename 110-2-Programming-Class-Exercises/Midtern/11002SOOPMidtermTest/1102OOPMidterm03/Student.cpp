#include "Student.h"

Student::Student()
{
	name = "Student" + to_string (count);
	id = count;
	count++;
}

Student::Student(std::string _name)
{
	if (existName.count(_name) == 1) {
		name = "Student" + to_string(count);
		cout << "Error:The name "<< _name <<" has exist.Use default name:Student." << endl;
	}
	else {
		name = _name;
		existName.insert(_name);
	}
	id = count;
	count++;
}

void Student::addGrade(std::string subject, float point)
{
	Sub temp;
	temp.subject = subject;
	temp.score = point;
	bool exist = 0;
	for (int i = 0; i < sub.size();i++) {
		if (sub[i].subject == subject){
			exist = 1;
			sub[i].score = point;
		}
	}
	if (!exist) {
		sub.push_back(temp);
	}
}

void Student::deleteGrade(std::string subject)
{
	bool exist = 0;
	for (int i = 0; i < sub.size(); i++) {
		if (sub[i].subject == subject) {
			exist = 1;
			sub.erase(sub.begin() + i);
			break;
		}
	}
	if (!exist) {
		cout << "Error:Subject " << subject << " not Found." << endl;
	}
}

void Student::deleteGrade()
{
	sub.clear();
}

void Student::printGrade()
{
	cout << "Id:" << id << " Name:" << name << endl;
	if (sub.size() == 0) {
		cout << "Error:Grade not Found." << endl;
	}
	for (auto val : sub) {
		cout << val.subject << " " << val.score << endl;
	}
}

int Student::count = 0;
set<string> Student::existName;