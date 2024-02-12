#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	char c[1000];
	scanf("%s", c);
	int len = strlen(c);
	int odd_sum = 0;
	int even_sum = 0;
	for (int i = 0; i < len; i++) {
		if (i % 2 == 0) odd_sum += (c[i] - '0');
		else even_sum += (c[i] - '0');
	}
	if (abs(odd_sum - even_sum) % 11 == 0) printf("%s is a multiple of 11.", c);
	else printf("%s is not a multiple of 11.", c);
    return 0;
}