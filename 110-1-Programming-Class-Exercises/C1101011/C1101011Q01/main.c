#include <stdio.h>

int main()
{
	int arr[2][2];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			scanf_s("%d", &arr[i][j]);
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			int t;
			scanf_s("%d", &t);
			arr[i][j] += t;
		}
	}
	printf("%d %d\n%d %d\n", arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
	return 0;
}