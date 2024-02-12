#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int function(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    else return function(x - 1) + function(x - 2);
}

int main()
{
    int n;
    scanf_s("%d", &n);
    if (n < 0) printf("\"Invalid input\"");
    else {
        printf("%d", function(n));
    }
    return 0;
}