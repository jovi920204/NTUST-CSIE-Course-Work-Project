#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
	int t;
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
int main()
{
	int n;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		char S[31], L[31];
		int s=0, l=0;
		scanf("%s", &S);
		for (int j = strlen(S) - 1, base = 1; j >= 0; j--, base <<= 1) {
			s += (S[j] - '0') * base;
		}
		scanf("%s", &L);
		for (int j = strlen(L) - 1,base = 1; j >= 0; j--,base <<= 1) {
			l += (L[j] - '0') * base;
		}
		printf("%d %d %d\n", strlen(S), strlen(L), gcd(s,l));
		if (gcd(s, l) == 1) printf("Pair #%d: Love is not all you need!\n",i);
		else printf("Pair #%d: All you need is love!\n",i);
	}
	
    return 0;
}