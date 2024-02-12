#pragma once
#include "Student.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

class Class
{
public:
	Class();
	void addStudent(Student student);

	void deleteStudent(Student student);

	void deleteStudent(std::string studentName);

	void printNumOfStudent(std::string subjectName);

	void printNumOfStudent();
	
	void printAvgScore(std::string subjectName);

	void printAvgScore();

	void printSubjectInformation();

	void printSubjectInformation(std::string subjectName);
	
	 vector<string> subjectList;
	 map<string, int> NumOfStudent;
	 map<string, float> avgScore;

	vector<Student> allStu;
	set<string> stu;
	
};

