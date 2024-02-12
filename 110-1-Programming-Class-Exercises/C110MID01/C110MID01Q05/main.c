#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	int many;
	int n;
	int a[9][9];
	int c[9][9] = { 0 };
	scanf("%d", &many);
	scanf("%d", &n);
	while(many--) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
				c[i][j] += a[i][j] ;
			}
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			printf("%d ", c[i][j]);
		}
		printf("%d\n", c[i][n]);
	}
	for (int i = 1; i < n; i++) {
		printf("%d ", c[n][i]);
	}
	printf("%d", c[n][n]);

	
    return 0;
}