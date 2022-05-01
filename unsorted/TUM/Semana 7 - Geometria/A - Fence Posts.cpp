#include <cstring>
#include <cstdio>
#include <algorithm>

int t, n, x[10010], y[10010], H[20020], P[10010], P2[10010];

int cross(int p, int q, int r) {
	return (x[q] - x[p]) * (y[r] - y[p]) - (y[q] - y[p]) * (x[r] - x[p]);
}

bool cmp(int i, int j) { return y[i] < y[j] || y[i] == y[j] && x[i] < x[j]; }

int main() {
	scanf("%d", &t);
	for (int i = 0; i < 10010; ++i)
		P2[i] = i;
	for (int T = 1; T <= t; ++T) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d %d", &x[i], &y[i]);

		int k = 0;
		memcpy(P, P2, n * sizeof(int));
		std::sort(P, P + n, cmp);
		for (int i = 0; i < n; ++i) {
			while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
				--k;
			H[k++] = P[i];
		}
		for (int i = n - 2, t = k + 1; i >= 0; --i) {
			while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)
				--k;
			H[k++] = P[i];
		}        
		std::sort(H, H + k - 1);
		printf("Case #%d:", T);
		for (int i = 0; i < k - 1; ++i)
			printf(" %d", H[i] + 1);
		printf("\n");
	}
}