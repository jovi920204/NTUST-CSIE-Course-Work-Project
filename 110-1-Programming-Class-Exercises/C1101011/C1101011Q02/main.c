#include <stdio.h>

int main()
{
	int a[2][2];
	int b[2][2];
	int arr[2][2];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			scanf_s("%d", &a[i][j]);
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			int t;
			scanf_s("%d", &b[i][j]);
		}
	}
	arr[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
	arr[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
	arr[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
	arr[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
	printf("%d %d\n%d %d\n", arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
	return 0;
}