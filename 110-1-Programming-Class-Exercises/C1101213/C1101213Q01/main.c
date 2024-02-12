#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main() {
	// 宣告所有需要用到的變數
	int n; // 輸入數字
	int weight = 1; 
	weight <<= 31; // 建立一個2的31次方
	int decimal = 0; // 紀錄反轉後的十進制數字
	int ispositive = 0; // 紀錄是否為正數
	int count_zero = 0, count_one = 0; // 紀錄0和1出現的次數
	scanf("%d", &n);
	int original = n; // 建立一哥變數紀錄原本的數值
	if (n >= 0) ispositive = 1;
	for (int i = 0; i < 32; i++) { // 先計算反轉後的十進制數值
		decimal += abs(weight) * abs(n % 2);
		if (n % 2 == 0) count_zero++;
		else count_one++;
		n >>= 1;
		weight >>= 1;
	}
	int ans_d = decimal;
	for (int i = 0; i < 32; i++) { // 再反轉回去，就會是我要的原本的值的二進制
		printf("%d", abs(decimal % 2));
		decimal >>= 1;
	}
	printf("\n");
	printf("Zeros: %d\n", count_zero);
	printf("Ones: %d\n", count_one);
	for (int i = 0; i < 32; i++) { // 再反轉一次，就是是反轉後的二進制
		printf("%d", abs(original % 2));
		original >>= 1;
	}
	printf("\n");
	printf("%d\n", ans_d);

	return 0;

}


///
/// -99									input
/// 11111111111111111111111110011101	binary
/// Zeros: 3							count zero
/// Ones: 29							count one
/// 10111001111111111111111111111111	reverse
/// -1174405121							decimal
/// 
/// >>
/// <<
/// &
/// |
/// ^
/// ~