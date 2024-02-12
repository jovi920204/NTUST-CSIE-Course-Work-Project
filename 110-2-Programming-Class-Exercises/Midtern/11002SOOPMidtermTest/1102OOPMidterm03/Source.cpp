#include "Recorder.h"
#include <iostream>
using namespace std;

int main()
{
	Student a = Student();
	Student b = Student("John");
	Student c = Student("John");
	Student d = Student("Student123");
	Student e = Student("Cena");

	a.addGrade("Chinese", 87);
	a.addGrade("OOP", 77);
	a.addGrade("OOP", 60);
	a.printGrade();

	b.printGrade();
	b.addGrade("OOP", 60);
	b.deleteGrade("OOP");
	b.deleteGrade("Chinese");
	b.addGrade("OOP", 60);
	b.printGrade();

	c.addGrade("OOP", 60);

	d.addGrade("English", 88);
	d.addGrade("OOP", 60);
	d.deleteGrade();
	d.addGrade("OOP", 60);
	d.printGrade();

	e.addGrade("English", 92);


	Class myClass;
	myClass.addStudent(a);
	myClass.addStudent(b);
	myClass.addStudent(c);
	myClass.addStudent(d);
	myClass.addStudent(e);
	myClass.addStudent(e);
	myClass.printSubjectInformation("English");
	myClass.printNumOfStudent();
	myClass.printNumOfStudent("Art");
	myClass.deleteStudent("a");
	myClass.deleteStudent(b);
	myClass.deleteStudent(e);
	myClass.printAvgScore();
	myClass.printAvgScore("OOP");
	myClass.printSubjectInformation("OOP");
	myClass.printSubjectInformation("Art");
	myClass.printSubjectInformation();

	myClass.printAvgScore();
	return 0;
}
