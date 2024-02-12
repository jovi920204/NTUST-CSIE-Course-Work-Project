#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int n;
	float ith[15][2];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%f %f", &ith[i][0], &ith[i][1]);
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (ith[j][0] == ith[j + 1][0]) {
				if (ith[j][1] > ith[j + 1][1]) {
					float y = ith[j][1];
					ith[j][1] = ith[j + 1][1];
					ith[j + 1][1] = y;
				}
			}
			else if (ith[j][0] > ith[j + 1][0]) {
				float x = ith[j][0];
				float y = ith[j][1];
				ith[j][0] = ith[j + 1][0];
				ith[j][1] = ith[j + 1][1];
				ith[j + 1][0] = x;
				ith[j + 1][1] = y;
			}
			
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%.2f %.2f\n", ith[i][0], ith[i][1]);
	}
    return 0;
}