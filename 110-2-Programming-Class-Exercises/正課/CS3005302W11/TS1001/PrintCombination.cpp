// Name: �i����
// Date: April, 27 , 2022  
// Last Update: April, 27 , 2022  
// Problem statement: Combinations
#include "PrintCombination.h"

void PrintCombination(int* a, int n, int r) {
	string ans = "";
	recursion(0, 0, n, r ,ans, a);
}

// ���j�禡
void recursion(int now, int level, int n, int r, string ans, int* a) {

	// �Y�h�Ƶ���n�����ƶq�A�N�ŦX����A��an�̲׭nans���r��[�W�{�b���Ʀr�ÿ�X
	if (level == r) { 
		ans += to_string(a[now - 1]);
		cout << ans << endl;
		return;
	}
	// �Ynow�����s�A���O�ڸ`�I�A�N��{�b���Ʀr�[�ians�̭�
	else if (now != 0) {
		ans += to_string(a[now - 1]);
		ans += " ";
	}
	// �Y�{�b���Ʀr����̫�@�ӼƦr�A���N�N��n�����ƶq����A�B�w�g���A�S��k�A���U�F�A�G���ŦX
	if (now == n) { 
		return;
	}
	// �b�P�@�hlevel��M��L���ڵ��I�A���U�h�ƦC�զX
	for (int i = now + 1; i <= n; i++) {
		recursion(i, level + 1, n, r, ans, a);
	}
}
