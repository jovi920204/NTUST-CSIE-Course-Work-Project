#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int fuc(int x) {
	if (x % 2 == 0) {
		x /= 2;
		fuc(x);
	}
	else if (x % 3 == 0) {
		x /= 3;
		fuc(x);
	}
	else if (x % 5 == 0) {
		x /= 5;
		fuc(x);
	}
	else return x;
}

int main()
{
	int n;
	scanf_s("%d", &n);
	if (n == 1) printf("It is an ugly number.");
	else {
		n = fuc(n);
		if (n == 1) printf("It is an ugly number.");
		else printf("It is not an ugly number.");

	}
    return 0;
}