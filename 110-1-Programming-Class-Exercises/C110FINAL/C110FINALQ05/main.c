#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert(char c) {
	switch (c) {
	case 'A':
	case 'B':
	case 'C':
		return 2;
	case 'D':
	case 'E':
	case 'F':
		return 3;
	case 'G':
	case 'H':
	case 'I':
		return 4;
	case 'J':
	case 'K':
	case 'L':
		return 5;
	case 'M':
	case 'N':
	case 'O':
		return 6;
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
		return 7;
	case 'T':
	case 'U':
	case 'V':
		return 8;
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		return 9;
	}
	defult:
		return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int j = 0; j < n; j++) {
		int hyphen = 0;
		int letter = 0;
		char phone[50] = { 0 };
		scanf("%s", phone);

		for (int i = 0; i < strlen(phone); i++) {
			if (isdigit(phone[i])) printf("%c", phone[i]);
			else if (phone[i] == '-') {
				printf("%c", phone[i]);
				hyphen++;
			}
			else {
				printf("%d", convert(phone[i]));
				letter++;
			}
			
		}
		printf(" %d %d\n", letter, hyphen);
	}
	return 0;
}

/*
2
1-HOME-SWEET-HOME
MY-MISERABLE-JOB
*/