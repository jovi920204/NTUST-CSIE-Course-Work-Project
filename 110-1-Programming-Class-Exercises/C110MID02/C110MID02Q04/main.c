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
	char seq1[150] = {0}, seq2[150];
	char seq3[150];
	char new[150] = { 0 };
	char subtext[150] = { 0 };
	int flag = 1;
	gets(seq1);
	gets(seq2);
	gets(seq3);
	int n1 = strlen(seq1);
	int n2 = strlen(seq2);
	int n3 = strlen(seq3);

	while(flag != 0){
		flag = 0;
		int des;
		char* ptr = strstr(seq1, seq2);
		for (int i = 0; i < n1; i++) {
			if (check(ptr, n2, seq2) == 1) {
				des = i;
				break;
			}
		}
		if (ptr == NULL) {
			flag = 0;
			break;
		}
		else {
			flag = 1;
			/*for (int i = 0; i < n1; i++) {
				if (seq1[i] == *ptr) {
					des = i;
					break;
				}
			}*/
			for (int i = 0; i < des; i++) {
				new[i] = seq1[i];
			}
			for (int i = 0, j = des; i < n3; i++, j++) {
				new[j] = seq3[i];
			}

			for (int i = des + n2, j = des + n3; i < n1; i++, j++) {
				new[j] = seq1[i];
			}
			strncpy(seq1, &new[0], strlen(new));
			n1 = strlen(seq1);
			//puts(seq1);
		}
	}
	puts(new);
	return 0;
}

/*Hello World!World World!!!
World!
C Programming

Hello C Programming!World !!!
World
C Programming
*/