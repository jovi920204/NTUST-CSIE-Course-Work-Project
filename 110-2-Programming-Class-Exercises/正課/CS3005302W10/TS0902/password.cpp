// Name: 張睿麟
// Date: April, 20 , 2022  
// Last Update: April, 20 , 2022  
// Problem statement: Namespace
#include "password.h"
string password;
namespace {
	bool isValid() {
		// password的長度必須大於等於8且一定要有一個字元不是字母
		if (password.length() >= 8) {
			for (int i = 0; i < password.length(); i++) {
				if (!isalpha(password[i])) {
					return 1;
				}
			}
			return 0;
		}
		else {
			return 0;
		}
	}
}
namespace Authenticate
{
	
	void inputPassword()
	{
		do
		{
			cout << "Enter your password (at least 8 characters " <<
				"and at least one non-letter)" << endl;
			cin >> password;
		} while (!isValid());
	}

	string getPassword()
	{
		return password;
	}
}


