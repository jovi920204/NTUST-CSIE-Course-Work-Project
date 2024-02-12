// Name: ±i∫Õ≈Ô
// Date: May, 8 , 2022  
// Last Update: May, 8 , 2022  
// Problem statement: Class Inheritance
#pragma once
#include <iostream>
using namespace std;

class Document
{
public:
	
	Document() {
		text = "";
	}
	Document(string str) {
		text = str;
	}
	const string getText() const;
protected:
	string text;

};

