#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main() {
	// �ŧi�Ҧ��ݭn�Ψ쪺�ܼ�
	int n; // ��J�Ʀr
	int weight = 1; 
	weight <<= 31; // �إߤ@��2��31����
	int decimal = 0; // ��������᪺�Q�i��Ʀr
	int ispositive = 0; // �����O�_������
	int count_zero = 0, count_one = 0; // ����0�M1�X�{������
	scanf("%d", &n);
	int original = n; // �إߤ@���ܼƬ����쥻���ƭ�
	if (n >= 0) ispositive = 1;
	for (int i = 0; i < 32; i++) { // ���p�����᪺�Q�i��ƭ�
		decimal += abs(weight) * abs(n % 2);
		if (n % 2 == 0) count_zero++;
		else count_one++;
		n >>= 1;
		weight >>= 1;
	}
	int ans_d = decimal;
	for (int i = 0; i < 32; i++) { // �A����^�h�A�N�|�O�ڭn���쥻���Ȫ��G�i��
		printf("%d", abs(decimal % 2));
		decimal >>= 1;
	}
	printf("\n");
	printf("Zeros: %d\n", count_zero);
	printf("Ones: %d\n", count_one);
	for (int i = 0; i < 32; i++) { // �A����@���A�N�O�O����᪺�G�i��
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