#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <string.h>

int check(char* sub, int n, char* target) {
    int issame = 1;
    for (int i = 0; i < n; i++) {
        if (sub[i] != target[i]) {
            issame = 0;
            break;
        }
    }
    return issame;
}

int main()
{
    //¥Îgets() and puts()
    char seq1[100] = { 0 }, seq2[100];
    char new[100];
    char subtext[100];
    int flag = 0;
    gets(seq1);
    gets(seq2);
    int n1 = strlen(seq1);
    int n2 = strlen(seq2);
    if (n2 > n1) {
        printf("Invalid pattern");
    }
    else {
        int des;
        for (des = 0; des < n1 - n2+1; des++) {
            strncpy(subtext, &seq1[des], n2);
            if (check(subtext,n2,seq2)) {
                flag = 1;
                break;
            }
        }
        for (int i = 0; i < des; i++) {
            new[i] = seq1[i];
        }
        for (int i = des + n2, j = des; i < n1; i++,j++) {
            new[j] = seq1[i];
        }
        if (flag == 0) printf("Pattern not found");
        else {
            for (int i = 0; i < n1 - n2; i++) {
                printf("%c", new[i]);
            }
        } 
    }
    
    return 0;
}