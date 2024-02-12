#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	int n,m;
	int times = 1;
	while (1) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0) break;
		char map[105][105] = { 0 };
		for (int i = 0; i < n; i++) {
			scanf("%s", map[i]);
		}
		if (times >= 2) printf("\n");
		printf("Field #%d:\n", times);
		//偵測周圍的區域有幾個*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int count = 0;
				if (map[i][j] == '*') continue;
				else {
					for (int x = -1; x <= 1; x++) {
						for (int y = -1; y <= 1; y++) {
							if (i + x >= 0 && i + x <= n) {
								if (j + y >= 0 && j + y <= m) {
									if (map[i + x][j + y] == '*') count++;
								}
							}
						}
					}
					map[i][j] = count + '0';
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			puts(map[i]);
		}
		times++;
	}
	return 0;
}
