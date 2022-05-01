#include <stdio.h>
#include <string.h>

int t, n, g[8][8], dp[8][1024], next[8][1024], k, j, i, v;

int TSP(int i, int m) {
	if (m == (1 << n) - 1) return dp[i][m] = g[i][0];
	int bj = -1, bv = (1 << 28), j, nm, v;
	for (j = 0; j < n; ++j) {
		if (i != j && !(m & (1 << j))) {
			nm = m | (1 << j);
			v = g[i][j] + (dp[j][nm] != -1 ? dp[j][nm] : TSP(j, nm));
			if (v < bv) {
				bv = v, bj = j;
			}
		}
	}
	next[i][m] = bj;
	return dp[i][m] = bv;
}

int main() {
	scanf("%d", &t);
	for (k = 1; k <= t; ++k) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				scanf("%d ", &g[i][j]);
		memset(dp, -1, sizeof dp);
		TSP(0, 1);
		printf("Case #%d:", k);
		j = v = 0;
		while (v != (1 << n) - 1) {
			printf(" %d", j + 1);
			v |= 1 << j;
			j = next[j][v];
		}
		printf("\n");
	}
}