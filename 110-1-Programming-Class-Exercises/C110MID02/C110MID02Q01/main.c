#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char s[25];
	int t[25];
	int time = 0;
	gets(s);
	for (int i = 0; i < strlen(s); i++) {
		t[i] = s[i] - '0';
		time += t[i] * 2 - 1;
	}
	time -= strlen(s) - 1;
	//printf("%d\n", time);
	for (int i = 0; i < strlen(s); i++) {
		int now = s[i] - '0';
		if (i == 0) {
			for (int j = 1; j <= now; j++) {
				for (int k = 0; k < j; k++) {
					printf("%d", j);
				}
				printf("\n");
			}
			for (int j = now - 1; j >= 1; j--) {
				for (int k = 0; k < j; k++) {
					printf("%d", j);
				}
				printf("\n");
			}
		}
		else {
			for (int j = 2; j <= now; j++) {
				for (int k = 0; k < j; k++) {
					printf("%d", j);
				}
				printf("\n");
			}
			for (int j = now - 1; j >= 1; j--) {
				for (int k = 0; k < j; k++) {
					printf("%d", j);
				}
				printf("\n");
			}
		}
	}
    return 0;
}