#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
    int n,t,flag = 0;
    int x = 0;
    int a[105];
    int b[105];
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (i != (n - 1)) {
            if (a[i] == a[i - 1] && a[i] != a[i + 1]) {
                b[x++] = a[i];
                flag = 1;
            }
        }
        else {
            if (a[i] == a[i - 1]) {
                b[x++] = a[i];
                flag = 1;
            }
        }
    }
    if (flag == 0) printf("No repeated number!\n");
    else {
        for (int i = 0; i < (x-1) ; i++) {
            printf("%d ", b[i]);
        }
        printf("%d\n", b[x-1]);
    }
    return 0;
}