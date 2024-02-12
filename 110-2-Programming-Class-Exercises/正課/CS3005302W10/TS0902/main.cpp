// Name: ±i∫Õ≈Ô
// Date: April, 20 , 2022  
// Last Update: April, 20 , 2022  
// Problem statement: Namespace
#include "password.h"
#include "user.h"
#include <iostream>
using namespace Authenticate;
int main()
{
	inputUserName();
	inputPassword();
	cout << "Your username is " << getUserName() <<
		" and your password is: " <<
		getPassword() << endl;
	return 0;
}
