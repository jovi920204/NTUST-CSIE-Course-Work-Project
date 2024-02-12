#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	int a[11] = { 0 };
	for (int i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < 10 - 1; i++) {
		for (int j = 0; j < 10 - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
	int now;
	int sum = 0;
	int flag = 0;
	for (int i = 0; i < 10; i++) {
		if (a[i] == a[i + 1] && flag == 0) {
			now = a[i];
			sum += a[i];
			flag = 1;
		}
		else if (a[i] == a[i + 1] && flag == 1) {
			continue;
		}
		if (a[i] != a[i + 1]) {
			flag = 0;
		}
	}
	printf("%d", sum);
    return 0;
}