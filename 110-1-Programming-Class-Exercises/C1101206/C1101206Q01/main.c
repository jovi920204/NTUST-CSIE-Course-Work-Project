#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
    int roman[200];
    roman['I'] = 1;roman['V'] = 5;roman['X'] = 10;roman['L'] = 50;roman['C'] = 100;roman['D'] = 500;roman['M'] = 1000;
    char s[15];
    gets(s);
    int sum = 0;
    for (int i = 0; i < strlen(s) - 1; i++) {
        if (roman[s[i]] < roman[s[i + 1]]) sum -= roman[s[i]];
        else sum += roman[s[i]];
        //printf("%d\n", sum);
    }
    sum += roman[s[strlen(s) - 1]];
    printf("%d\n", sum);
    return 0;
}


///Symbol       Value
///I             1
///V             5
///X             10
///L             50
///C             100
///D             500
///M             1000
/// 
///•	I can be placed before V (5) and X (10) to make 4 and 9.
///•	X can be placed before L(50) and C(100) to make 40 and 90.
///•	C can be placed before D(500) and M(1000) to make 400 and 900.
///     
///     IV = 4
///     IX = 9
///     XL = 40
///     XC = 90
///     CD = 400
///     CM = 900 