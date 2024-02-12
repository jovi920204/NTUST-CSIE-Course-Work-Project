#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
void simp(char* a, int sign);
int cmp(char* a, char* b);
void reverse(char* a);
void zero(char* a, char* b);
void add(char* a, char* b, char* ans);
void sub(char* a, char* b, char* ans);


int main()
{
	int n;
	scanf("%d\n", &n);
	while (n--) {
		int flag = 0;
		char input[300] = { 0 };
		char str1[50] = { 0 },  str2[50] = { 0 };
		char ans[50] = { 0 };
		char sym;
		gets(input);
		int i = 0;
		int j = 0;
		while (input[i] != '+' && input[i] != '-') {
			str1[j++] = input[i++];
		}
		sym = input[i++];
		j = 0;
		while (i < strlen(input)) {
			str2[j++] = input[i++];
		}
		zero(str1, str2);
		if (sym == '+') add(str1, str2, ans);
		else if (sym == '-') sub(str1, str2, ans);
		//printf("%d\n", cmp(str1, str2));
	}
	return 0;
}
void simp(char* a, int sign) {
	char ten[50] = { 0 };
	char dec[50] = { 0 };
	int flag = 0;
	for (int i = 0,j=0; i < strlen(a); i++) {
		if (flag == 0 && a[i] != '.') ten[j++] = a[i];
		else if (a[i] == '.') {
			flag = 1;
			j = 0;
		}
		else if (flag == 1 && a[i] != '.') dec[j++] = a[i];
	}
	/*printf("QQ\n");
	printf("%d ", strlen(a));
	puts(a);
	printf("%d ", strlen(ten));
	puts(ten);
	printf("%d ", strlen(dec));
	puts(dec);
	printf("QQ\n");*/
	int i = 0;
	int ten_head = 0;
	int dec_tail = 0;
	while (ten[i++] == '0') {
		ten_head++;
	}
	reverse(dec);
	i = 0;
	while (dec[i++] == '0') {
		dec_tail++;
	}
	reverse(dec);
	//printf("ten_head = %d\n", ten_head);
	//printf("dec_tail = %d\n", dec_tail);
	if (sign == 0) printf("-");
	if ((strlen(ten) - ten_head) == 0 && (strlen(dec) - dec_tail) == 0) { //代表沒有整數及小數
		printf("0\n");
	}
	else if ((strlen(ten) - ten_head) == 0) { //沒整數部分 但有小數部分
		printf("0.");
		for (int i = 0; i < strlen(dec) - dec_tail; i++) {
			printf("%c", dec[i]);
		}
	}
	else if ((strlen(dec) - dec_tail) == 0) { //沒小數部分 但有整數部分
		for (int i = ten_head; i < strlen(ten); i++) {
			printf("%c", ten[i]);
		}
	}
	else { //有整數及小數
		for (int i = ten_head; i < strlen(a) - dec_tail; i++) {
			printf("%c", a[i]);
		}
	}
	printf("\n");
}
int cmp(char* a, char* b) { // a > b return 1
	for (int i = 0; i < strlen(a); i++) {
		//printf("%c %c\n", a[i], b[i]);
		if (a[i] > b[i]) return 1;
		else if (a[i] < b[i]) return 0;
		else continue;
	}
}
void reverse(char* a) {
	for (int i = 0, j = strlen(a) - 1; i <= j; i++, j--) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}
void zero(char* a, char* b) {
	int flag1 = 0, flag2 = 0;
	int ten1 = 0, ten2 = 0;
	int de1 = 0, de2 = 0;
	for (int i = 0; i < strlen(a); i++) { //計算整數和小數各有多少
		if (isdigit(a[i]) && flag1 == 0) ten1++;
		else if (!isdigit(a[i])) flag1 = 1;
		else if (isdigit(a[i]) && flag1 == 1) de1++;
	}
	for (int i = 0; i < strlen(b); i++) { //計算整數和小數各有多少
		if (isdigit(b[i]) && flag2 == 0) ten2++;
		else if (!isdigit(b[i])) flag2 = 1;
		else if (isdigit(b[i]) && flag2 == 1) de2++;
	}
	//printf("%d %d %d %d\n", ten1, de1, ten2, de2);
	if (ten1 != ten2) {
		if (ten1 > ten2) {
			reverse(b);
			int i = strlen(b);
			int count = ten1 - ten2;
			while (count--) {
				b[i] = '0';
				i++;
			}
			reverse(b);
		}
		else if (ten2 > ten1) {
			reverse(a);
			int i = strlen(a);
			int count = ten2 - ten1;
			while (count--) {
				a[i] = '0';
				i++;
			}
			reverse(a);
		}
	}
	if (de1 != de2) {
		if (de1 == 0) a[strlen(a)] = '.';
		if (de2 == 0) b[strlen(b)] = '.';
		if (de1 > de2) {
			int i = strlen(b);
			int count = de1 - de2;
			while (count--) {
				b[i] = '0';
				i++;
			}
		}
		else if (de2 > de1) {
			int i = strlen(a);
			int count = de2 - de1;
			while (count--) {
				a[i] = '0';
				i++;
			}
		}
	}
	//puts(a);
	//puts(b);
}
void add(char* a, char* b, char* ans) {
	reverse(a);
	reverse(b);
	int carry = 0;
	for (int i = 0; i < strlen(a); i++) {
		//printf("QQ\n");
		if (a[i] == '.') {
			ans[i] = '.';
		}
		else {
			int x = a[i] - '0';
			int y = b[i] - '0';
			int z = x + y + carry;
			carry = z / 10;
			z = z%10;
			ans[i] = z + '0';
		}
	}
	if (carry != 0) {
		ans[strlen(ans)] = carry + '0';
	}
	reverse(a);
	reverse(b);
	reverse(ans);
	simp(ans, 1);
	/*for (int i = head; i < ans_len; i++) {
		printf("%c", ans[i]);
	}
	printf("\n");*/
}
void sub(char* a, char* b, char* ans) {
	// 策略
	// 全部先借位
	// 做減法
	// 再把每一位做修正
	int flag = cmp(a, b);
	// 借位
	
	/*for (int i = 0; i < strlen(a) - 1; i++) {
		if (a[i] == '.') continue;
		else if (a[i] - '0' > 0 && a[i] > a[i+1]) {
			a[i]--;
			if (a[i+1] != '.') a[i + 1] += 10;
			else {
				a[i + 2] += 10;
			}
		}
		else if (a[i] - '0' == 0) continue;
	}
	for (int i = 0; i < strlen(b) - 1; i++) {
		if (b[i] == '.') continue;
		else if (b[i] - '0' > 0 && b[i] > b[i+1]) {
			b[i]--;
			if (b[i + 1] != '.') b[i + 1] += 10;
			else {
				b[i + 2] += 10;
			}
		}
		else if (b[i] - '0' == 0) continue;
	}*/
	/*for (int i = 0; i < strlen(a); i++) {
		if (a[i] != '.') printf("%2d ", (int)(a[i] - '0'));
		else printf("%c ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < strlen(b); i++) {
		if (b[i] != '.') printf("%2d ", (int)(b[i] - '0'));
		else printf("%c ", b[i]);
	}*/
	// 相減
	if (flag == 1) {
		for (int i = 0; i < strlen(a) - 1; i++) {
			if (a[i] == '.') continue;
			else if (a[i] - '0' > 0 && a[i] > a[i + 1]) {
				a[i]--;
				if (a[i + 1] != '.') a[i + 1] += 10;
				else {
					a[i + 2] += 10;
				}
			}
			else if (a[i] - '0' == 0) continue;
		}
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] != '.') ans[i] = a[i] - b[i] + '0';
			else if (a[i] == '.') ans[i] = '.';
			//printf("%d\n",(int)(ans[i]-'0'));
		}
	}
	else {
		for (int i = 0; i < strlen(b) - 1; i++) {
			if (b[i] == '.') continue;
			else if (b[i] - '0' > 0 && b[i] > b[i + 1]) {
				b[i]--;
				if (b[i + 1] != '.') b[i + 1] += 10;
				else {
					b[i + 2] += 10;
				}
			}
			else if (b[i] - '0' == 0) continue;
		}
		for (int i = 0; i < strlen(b); i++) {
			if (b[i] != '.') ans[i] = b[i] - a[i] + '0';
			else if (b[i] == '.') ans[i] = '.';
		}
	}
	// 修正
	reverse(ans);
	int carry = 0;
	for (int i = 0; i < strlen(ans); i++) {
		//printf("QQ\n");
		if (ans[i] == '.') continue;
		else {
			int x = ans[i] - '0';
			int z = carry + x;
			carry = z / 10;
			ans[i] = z%10 + '0';
		}
	}
	if (carry != 0) {
		ans[strlen(ans)] = carry + '0';
	}
	reverse(ans);
	// 輸出
	simp(ans, flag);
	/*if (flag == 0) printf("-");
	for (int i = head; i < ans_len; i++) {
		printf("%c", ans[i]);
	}
	printf("\n");*/
	
}

///printf("QQ\n");


///5
///12345678991019231124+1234567890000000
///12345678991019231124 - 1234567890000000
///1 - 123456789123456789
///123465789.123456789 + 987654321.987654321
///1000000000 - 0.1
/// 
/// 
/// 1  2  3  3  4  .  5  
/// 0 12  3  3  4  .  5
/// 0 11 13  3  4  .  5
/// 0 11 12 13  4  .  5
/// 0 11 12 12 14  .  5
/// 0 11 12 12 13  . 15