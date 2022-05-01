#include <string.h>
#include <stdio.h>

char b[10][10] = {0};
int t, ok[100], ql[10], qc[10], qb[10], cl, cc, cb, hl, hc, hb, bi, bj, bii, bjj, g[100][100],
	gs[100], q[100], qs, val[100], tmp[100][100], tmps;

// int validate() {  // validates a correct puzzle
// 	for (int i = 0; i < 9; ++i) {
// 		hl = hc = hb = 0;
// 		bi = 3 * (i / 3), bj = 3 * (i % 3);
// 		for (int j = 0; j < 9; ++j) {
// 			bii = bi + j % 3, bjj = bj + j / 3;
// 			hl |= (1 << (b[i][j] - '0'));
// 			hc |= (1 << (b[j][i] - '0'));
// 			hb |= (1 << (b[bii][bjj] - '0'));
// 		}
// 		if (hl != 1022 || hc != 1022 || hb != 1022) return 0;
// 	}
// 	return 1;
// }

void populate(int* q, int c, int h) {
	for (int i = 0; i < c; ++i) {
		for (int j = i + 1; j < c; ++j) {
			int in = 0;
			for (int k = 0; k < gs[q[i]]; ++k)
				if (g[q[i]][k] == q[j]) in = 1;
			if (!in) g[q[i]][gs[q[i]]++] = q[j];
			in = 0;
			for (int k = 0; k < gs[q[j]]; ++k)
				if (g[q[j]][k] == q[i]) in = 1;
			if (!in) g[q[j]][gs[q[j]]++] = q[i];
		}
		ok[q[i]] |= h;
	}
}

int bt(int i) {
	if (ok[i] == 1022) return 0;
	for (int j = 1; j <= 9; ++j) {
		if (!(ok[i] & (1 << j))) {
			val[i] = j;
			int yes = 1, ts = tmps++;
			for (int k = 0; k < gs[i]; ++k) {
				tmp[ts][k] = ok[g[i][k]];
				ok[g[i][k]] |= (1 << j);
			}
			for (int k = 0; k < gs[i] && yes; ++k)
				if (val[g[i][k]] == -1) yes = yes && bt(g[i][k]);
			if (!yes) {
				for (int k = 0; k < gs[i]; ++k)
					ok[g[i][k]] = tmp[ts][k];
				val[i] = -1;
				--tmps;
			} else {
				--tmps;
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		memset(ok, 0, sizeof ok);
		memset(gs, 0, sizeof gs);
		memset(val, -1, sizeof val);
		for (int i = 0; i < 9; ++i)
			scanf("%s\n", b[i]);
		qs = 0;
		for (int i = 0; i < 9; ++i) {
			cc = cl = cb = hl = hc = hb = 0;
			bi = 3 * (i / 3), bj = 3 * (i % 3);
			for (int j = 0; j < 9; ++j) {
				if (b[i][j] != '?')
					hl |= (1 << (b[i][j] - '0'));
				else {
					ql[cl++] = i * 9 + j;
					q[qs++] = i * 9 + j;
				}
				if (b[j][i] != '?')
					hc |= (1 << (b[j][i] - '0'));
				else
					qc[cc++] = j * 9 + i;
				bii = bi + j % 3, bjj = bj + j / 3;
				if (b[bii][bjj] != '?')
					hb |= (1 << (b[bii][bjj] - '0'));
				else
					qb[cb++] = bii * 9 + bjj;
			}
			populate(ql, cl, hl);
			populate(qc, cc, hc);
			populate(qb, cb, hb);
		}
		for (int i = 0; i < qs; ++i)
			for (int j = 1; j <= 9; ++j)
				if (1022 - ok[q[i]] == (1 << j)) {
					val[q[i]] = j;
					for (int k = 0; k < gs[q[i]]; ++k)
						ok[g[q[i]][k]] |= (1 << j);
					break;
				}

		for (int i = 0; i < qs; ++i)
			if (val[q[i]] == -1) {
				tmps = 0;
				bt(q[i]); /* assume input is well-formed so bt will always return true */
			}
		for (int i = 0; i < qs; ++i)
			b[q[i] / 9][q[i] % 9] = '0' + val[q[i]];
		printf("Case #%d:\n", T);
		for (int i = 0; i < 9; ++i)
			printf("%s\n", b[i]);
		// printf("valid: %d\n", validate());
		if (T != t) printf("\n");
	}
}