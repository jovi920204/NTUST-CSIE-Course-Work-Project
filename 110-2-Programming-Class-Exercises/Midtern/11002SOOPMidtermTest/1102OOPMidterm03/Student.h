#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

struct Sub {
	string subject;
	float score;
};
class Student
{
public:

	Student();
	Student(std::string _name);
	void addGrade(std::string subject, float point);
	void deleteGrade(std::string subject);
	void deleteGrade();
	void printGrade();
	
	vector<Sub> sub;
	string name;
	int id;
	static int count;
	static set<string> existName;
};

