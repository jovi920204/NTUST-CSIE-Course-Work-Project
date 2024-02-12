#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	int n;
	scanf_s("%d", &n);
	if (n < 2 || n > 20) printf("Invalid input");
	else {
		if (n % 2 == 0) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i; j++) { //n次
					printf(" ");
				}
				for (int j = 0; j < n - i; j++) {
					printf("*");
				}
				for (int j = 0; j < n - i - 1; j++) {
					printf("*");
				}
				printf("\n");
			}
			for (int i = n-2; i >= 0; i--) {
				for (int j = i; j > 0; j--) {
					printf(" ");
				}
				for (int j = n-i; j > 0; j--) {
					printf("*");
				}
				for (int j = n-i-1; j > 0; j--) {
					printf("*");
				}
				printf("\n");
			}
		}
		else { // n is odd number
			int head = n; //最外層的星星數
			int times = n * 2 - 1;//次數
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i ; j++) { //n次
					printf(" ");
				}
				for (int j = 0; j < n-i; j++) { 
					printf("*");
				}
				for (int j = 0; j < n - i - 1; j++) {
					printf("*");
				}
				printf("\n");
			}
			for (int i = n-2; i >=0; i--) {
				for (int j = i; j > 0; j--) {
					printf(" ");
				}
				for (int j = n-i; j > 0; j--) {
					printf("*");
				}
				for (int j = n-i-1; j > 0; j--) {
					printf("*");
				}
				printf("\n");
			}

		}

	}

    return 0;
}