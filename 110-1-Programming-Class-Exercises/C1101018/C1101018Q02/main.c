#include <stdio.h>

int main()
{
    int n;
    scanf_s("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = n - i; j > 0; j--) {
            printf(" ");
        }
        for (int k = 0; k < i * 2 - 1; k++) {
            printf("%c", i + 64);
        }
        printf("\n");
    }
    return 0;
}