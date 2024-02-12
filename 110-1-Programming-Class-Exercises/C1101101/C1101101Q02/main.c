#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    int c = *(int*)a;
    int d = *(int*)b;
    if (c < d) return -1;
    else if (c == d) return 0;
    else return 1;
}

int main()
{
    int n;
    scanf_s("%d", &n);
    int num[13];
    int index[205] = {0};
    for (int i = 0; i < n; i++) {
        int t;
        scanf_s("%d", &t);
        num[i] = t + 100;
        index[num[i]] = i;
    }
    qsort((void*)num, n, sizeof(num[0]), compare);
    for (int i = 0; i < n-1; i++) {
        printf("%d ", index[num[i]]);
    }
    printf("%d", index[num[n-1]]);
    return 0;
}