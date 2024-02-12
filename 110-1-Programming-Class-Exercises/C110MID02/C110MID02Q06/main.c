#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("Case #%d:\n", i);
		char str[35];
		//int ch, i = 0;
		 /*do {
			while ((ch = getchar()) != '\n') {
				if (i < n) {
					str[i++] = ch;
				}
			}
			str[i] = '\0';
			//do something
			printf("%c \n", str[0]);
		 } while (strlen(str) != 0);
		 */

		/*while (str[1] != '\0' || i == 1) {
			 gets(str);
			 printf("%c\n",str[0]);

		 }*/
		while (1) {
			int ch, j = 0;
			while ((ch = getchar()) != '\n' && (ch = getchar()) != '\0') {
				if (j < n) {
					str[j++] = ch;
				}
			}
			printf("QQ\n");
			str[j] = '0';
			if (j == 0) break;
		}
	}
    return 0;
}

/*
'H'ey g'o'od la'w'yer
as I previously previewed
yam does a soup

First I give money to Teresa
after I inform dad of
your horrible soup


*/