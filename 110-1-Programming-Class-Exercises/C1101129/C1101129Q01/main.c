#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	char s[105];
	int n;
	gets(s);
	scanf("%d", &n);
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			if (s[i] + n > 'z') {
				s[i] = s[i] + n - 'z' + 'a' - 1;
			}
			else s[i] += n;
		}
		if (s[i] >= 'A' && s[i] <= 'Z') {
			if (s[i] + n > 'Z') {
				s[i] = s[i] + n - 'Z' + 'A' - 1;
			}
			else s[i] += n;
		}
		else continue;
	}
	for (int i = 0; i < strlen(s); i++) {
		printf("%c", s[i]);
	}
	return 0;
}