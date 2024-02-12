// Name: 眎和棚
// Date: April, 27 , 2022  
// Last Update: April, 27 , 2022  
// Problem statement: Combinations
#include "PrintCombination.h"

void PrintCombination(int* a, int n, int r) {
	string ans = "";
	recursion(0, 0, n, r ,ans, a);
}

// 患癹ㄧΑ
void recursion(int now, int level, int n, int r, string ans, int* a) {

	// 璝糷计单璶计秖碞才兵ンрan程沧璶ans﹃瞷计块
	if (level == r) { 
		ans += to_string(a[now - 1]);
		cout << ans << endl;
		return;
	}
	// 璝nowぃ箂ぃ琌竊翴碞р瞷计秈ans柑
	else if (now != 0) {
		ans += to_string(a[now - 1]);
		ans += " ";
	}
	// 璝瞷计单程计ê碞璶计秖ゼ竒┏⊿快猭┕珿ぃ才
	if (now == n) { 
		return;
	}
	// 糷levelт碝ㄤ挡翴┕逼舱
	for (int i = now + 1; i <= n; i++) {
		recursion(i, level + 1, n, r, ans, a);
	}
}
