// Name: ±i∫Õ≈Ô
// Date: May, 8 , 2022  
// Last Update: May, 8 , 2022  
// Problem statement: Class Inheritance
#pragma once
#include "Document.h"
class File :  public Document
{
public:
	File() {
		text = "";
		pathName = "";
	}
	File(string str1, string str2) {
		text = str1;
		pathName = str2;
	}

	void setPathname(string name);
	string getPathname();
private:
	string pathName;
};

