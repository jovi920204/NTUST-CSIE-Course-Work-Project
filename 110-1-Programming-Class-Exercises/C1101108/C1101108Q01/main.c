#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <math.h>
int counter = 0;
int step; // 2^n-1 ²¾°Ê¨B¼Æ

void hanoi(int n, char a, char b, char c) {
	//if (counter == 2) printf("Disk %d moved from %c to %c\n", n, a, c);
	if (n == 1) {
		counter++;
		if (counter == step) printf("Disk %d moved from %c to %c", n, a, c);
	}
	else {
		hanoi(n - 1, a, c, b);
		counter++;
		if (counter == step) printf("Disk %d moved from %c to %c", n, a, c);
		hanoi(n - 1, b, a, c);
	}

}

int main()
{
	int n;
	scanf_s("%d", &n);
	scanf_s("%d", &step);
	if (n < 1) printf("Invalid disk number");
	else if (step > pow(2, n) - 1) printf("Step out of range");
	else {
		char a = 'A';
		char b = 'B';
		char c = 'C';
		hanoi(n, a, b, c);
	}
    return 0;
}