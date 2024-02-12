#include <stdio.h>

int main()
{
    float m, n;
    char c;
    scanf_s("%f %c %f", &m, &c, 1, &n);
    if (c == '+') {
        printf("%.2f %c %.2f = %.2f\n", m, c, n, m + n);
    }
    else if (c == '-') {
        printf("%.2f %c %.2f = %.2f\n", m, c, n, m - n);
    }
    else if (c == '*') {
        printf("%.2f %c %.2f = %.2f\n", m, c, n, m * n);
    }
    else if (c == '/') {
        if (n == 0) {
            printf("Division by zero\n");
        }
        else {
            printf("%.2f %c %.2f = %.2f\n", m, c, n, m / n);
        }
    }
    
    return 0;
}