#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool checkSudoku(vector<vector<int>>& mySudoku);

int main()
{
    while (true)
    {
        vector<vector<int>> mySudoku(9);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char temp;
                cin >> temp;

                if (temp == ',')
                {
                    j--;
                    continue;
                }
                else
                {
                    mySudoku[i].push_back(temp - '0');
                }
            }
        }
        if (cin.eof())
        {
            break;
        }
        if (checkSudoku(mySudoku) == false)
        {
            cout << "False" << endl;
        }
        else
        {
            cout << "True" << endl;
        }

    }

}

bool checkSudoku(vector<vector<int>>& mySudoku)
{
    
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            int sum = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    sum += mySudoku[i + r * 3][j + c * 3];

                }
            }
            if (sum != 45) {
                return 0;
            }
        }
    }
    return 1;
}