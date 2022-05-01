#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

int t, n, m, k, a, b, gs[64], g[64][12], ok[64], val[64], tmp[64][12], tmps, ans;

// int validate() {
// 	for (int i = 1; i <= n; ++i) {
// 		if (val[i] == -1) {
// 			assert(0);
// 			return 0;
// 		}
// 		for (int j = 0; j < gs[i]; ++j)
// 			if (val[i] == val[g[i][j]]) {
// 				printf("val[%d] = val[%d] = %d\n", i, g[i][j], val[i]);
// 				assert(0);
// 				return 0;
// 			}
// 	}
// 	return 1;
// }

int bt(int i) {
	if (ok[i] == (1 << k) - 1) return 0;
	for (int j = 0; j < k; ++j)
		if (!(ok[i] & (1 << j))) {
			val[i] = j;
			int yes = 1, ts = tmps++;
			for (int l = 0; l < gs[i]; ++l) {
				tmp[ts][l] = ok[g[i][l]];
				ok[g[i][l]] |= (1 << j);
			}
			for (int l = 0; l < gs[i] && yes; ++l) {
				if (val[g[i][l]] == j) {
					ok[i] |= (1 << j);
					goto lv;
				}
				if (val[g[i][l]] == -1) yes = yes && bt(g[i][l]);
			}
			if (!yes) {
			lv:
				for (int l = 0; l < gs[i]; ++l)
					ok[g[i][l]] = tmp[ts][l];
				val[i] = -1;
				--tmps;
			} else {
				--tmps;
				return 1;
			}
		}
	return 0;
}

int main() {
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		scanf("%d %d %d", &n, &m, &k);
		memset(gs, 0, sizeof gs);
		memset(ok, 0, sizeof ok);
		memset(val, -1, sizeof val);
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a, &b);
			g[a][gs[a]++] = b;
			g[b][gs[b]++] = a;
		}
		// printf("n, m, k = (%d, %d, %d)\n", n, m, k);
		printf("Case #%d:", T);
		tmps = 0, ans = 1;
		for (int i = 1; i <= n && ans; ++i)
			if (val[i] == -1) ans = ans && bt(i);
		if (!ans)
			printf(" impossible\n");
		else {
			for (int i = 1; i <= n; ++i)
				printf(" %d", val[i] + 1);
			printf("\n");
			// printf("valid: %d\n", validate());
		}
	}
}