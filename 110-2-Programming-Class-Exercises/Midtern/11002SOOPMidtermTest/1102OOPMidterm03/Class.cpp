#include "Class.h"
#include "Student.h"

Class::Class()
{
}

void Class::addStudent(Student student)
{
	if (stu.count(student.name) == 1) {
		cout << "Error:The student " << student.name << " has in class." << endl;
	}
	else {
		for (int i = 0; i < student.sub.size(); i++) {
			if (NumOfStudent[student.sub[i].subject] == 0) {
				subjectList.push_back(student.sub[i].subject);
			}
			NumOfStudent[student.sub[i].subject]++;
			avgScore[student.sub[i].subject] += student.sub[i].score;
		}
		stu.insert(student.name);
		allStu.push_back(student);
	}
}

void Class::deleteStudent(Student student)
{
	//Delete student from Class.
	for (int i = 0; i < allStu.size(); i++) {
		if (allStu[i].name == student.name) {
			for (int j = 0; j < student.sub.size(); j++) {
				NumOfStudent[student.sub[j].subject]--;
				avgScore[student.sub[j].subject] -= student.sub[j].score;
				if (NumOfStudent[student.sub[j].subject] == 0) {
					subjectList.erase(find(subjectList.begin(), subjectList.end(), student.sub[j].subject));
				}
			}
			allStu.erase(allStu.begin() + i);
			break;
		}
	}
}

void Class::deleteStudent(std::string studentName)
{
	//Delete student from Class.
	//If studentName not found, print¡¨ Error : Student studentName not found.¡§
	for (int i = 0; i < allStu.size(); i++) {
		if (allStu[i].name == studentName) {
			allStu.erase(allStu.begin() + i);
			return;
		}
	}
	cout << "Error:Student " << studentName << " not found." << endl;
}

void Class::printNumOfStudent(std::string subjectName)
{
	//Print the subject nameand its number of students.
	//If subjectName not found, print¡¨ Error : Subject subjectName not found.
	//e.g.OOP 4
	if (NumOfStudent[subjectName] == 0) {
		cout << "Error:Subject "<< subjectName << " not found." << endl;
	}
	else {
		cout << subjectName << " " << NumOfStudent[subjectName] << endl;
	}
}

void Class::printNumOfStudent()
{
	//Print all of subject nameand its number of students.
	for (auto val : subjectList) {
		if (NumOfStudent[val] != 0) {
			cout << val << " " << NumOfStudent[val] << endl;
		}	
	}
}

void Class::printAvgScore(std::string subjectName)
{
	//Print the subject nameand its average score.
	//e.g.OOP 60
	//If subjectName not found, print¡¨ Error : Subject subjectName not found.
	if (NumOfStudent[subjectName] == 0) {
		cout << "Error:Subject "<< subjectName <<" not found." << endl;
	}
	else {
		cout << subjectName << " " << avgScore[subjectName] / NumOfStudent[subjectName] << endl;
	}
}

void Class::printAvgScore()
{
	//Print all of the subject nameand its average score.
	for (int i = 0; i < subjectList.size(); i++) {
		cout << subjectList[i] << " " << avgScore[subjectList[i]] / NumOfStudent[subjectList[i]] << endl;
	}
}

void Class::printSubjectInformation()
{
	for (int i = 0; i < subjectList.size(); i++) {
		cout << "Subject name:" << subjectList[i] << endl;
		cout << "Num of students:" << NumOfStudent[subjectList[i]] << endl;
		for (auto val : allStu) {
			for (auto val2 : val.sub) {
				if (val2.subject == subjectList[i]) {
					cout << val.name << " " << val2.score << endl;
				}
			}
		}
	}
}

void Class::printSubjectInformation(std::string subjectName)
{
	if (NumOfStudent[subjectName] == 0) {
		cout << "Error:Subject " << subjectName << " not found." << endl;
		return;
	}
	cout << "Subject name:" << subjectName << endl;
	cout << "Num of students:" << NumOfStudent[subjectName] << endl;
	for (auto val : allStu) {
		for (auto val2 : val.sub) {
			if (val2.subject == subjectName) {
				cout << val.name << " " << val2.score << endl;
			}
		}
	}
}


