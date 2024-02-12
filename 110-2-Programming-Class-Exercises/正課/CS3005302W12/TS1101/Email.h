// Name: ±i∫Õ≈Ô
// Date: May, 8 , 2022  
// Last Update: May, 8 , 2022  
// Problem statement: Class Inheritance
#pragma once
#include "Document.h"
class Email : public Document
{
public:
	Email() {
		text = "";
	}
	Email(string str1, string str2, string str3, string str4){
		text = str1;
		sender = str2;
		recipient = str3;
		title = str4;
	}
	string getSender();
	string getRecipient();
	string getTitle();

private:
	string sender, recipient, title;

};

