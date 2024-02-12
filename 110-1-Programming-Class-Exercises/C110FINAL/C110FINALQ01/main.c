#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char input[22];
	int num[22] = { 0 };
	int max = 0;
	gets(input);
	for (int i = 0; i < strlen(input); i++) {
		num[i] = input[i] - '0';
		if (num[i] >= max) max = num[i];
	}

	for (int i = 0; i < strlen(input); i++) {
		int t = input[i] - '0';
		if (i == 0) {
			for (int j = 0; j < t/2+1; j++) {
				// j*2+1
				for (int k = 0; k < max / 2+1 - ((j * 2 + 1) / 2 + 1); k++) { // space
					printf(" ");
				}
				for (int k = 0; k < j*2+1; k++) {
					printf("%d", j * 2 + 1);
				}
				printf("\n");
			}
			for (int j = t / 2 ; j > 0; j--) {
				for (int k = 0; k < max / 2+1 -((j*2-1)/2+1); k++) { // space
					printf(" ");
				}
				for (int k = 0; k < j*2-1; k++) {
					printf("%d", j * 2 - 1);
				}
				printf("\n");
			}
		}
		else {
			for (int j = 1; j < t / 2 + 1; j++) {
				// j*2+1
				for (int k = 0; k < max / 2 + 1 - ((j * 2 + 1) / 2 + 1); k++) { // space
					printf(" ");
				}
				for (int k = 0; k < j * 2 + 1; k++) {
					printf("%d", j * 2 + 1);
				}
				printf("\n");
			}
			for (int j = t / 2; j > 0; j--) {
				for (int k = 0; k < max / 2 + 1 - ((j * 2 - 1) / 2 + 1); k++) { // space
					printf(" ");
				}
				for (int k = 0; k < j * 2 - 1; k++) {
					printf("%d", j * 2 - 1);
				}
				printf("\n");
			}
		}
	}
	return 0;
}

/*
input 3
output

X1X
333
X1X

input 5
output

XX1XX
X333X
55555
X333X
XX1XX
*/