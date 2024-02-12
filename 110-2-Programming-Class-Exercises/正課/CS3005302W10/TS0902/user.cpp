// Name: 張睿麟
// Date: April, 20 , 2022  
// Last Update: April, 20 , 2022  
// Problem statement: Namespace
#include "user.h"

namespace {
		bool isValid() {
			// username 必須剛好8個字且全部為字母
			if (username.length() == 8) {
				for (int i = 0; i < 8; i++) {
					if (!isalpha(username[i])) {
						return 0;
					}
				}
				return 1;
			}
			else {
				return 0;
			}
		}
	}
namespace Authenticate
{
	string username;
	void inputUserName()
	{
		do
		{
			cout << "Enter your username (8 letters only)" << endl;
			cin >> username;
		} while (!isValid());
	}

	string getUserName()
	{
		return username;
	}
}
