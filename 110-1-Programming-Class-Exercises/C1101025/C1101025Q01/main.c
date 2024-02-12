#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
    int n;
    int a[100];
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &a[i]);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < n-1; i++) {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[n - 1]);
    return 0;
}