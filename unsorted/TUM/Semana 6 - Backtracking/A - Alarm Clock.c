#include <stdio.h>
#include <string.h>
#define cb(a, b, c) (((sg[a] & sg[b]) == sg[a]) && !((sg[a] ^ sg[b]) & OR[c]))

unsigned t, n, sg[] = {119, 20, 59, 62, 92, 110, 111, 52, 127, 126};
unsigned h[20], m[20], k, i, h1, m1, ok, h2, m2, OR[4];

int main() {
	scanf("%d", &t);
	for (k = 1; k <= t; ++k) {
		scanf("%d", &n);
		memset(OR, 0, sizeof OR);
		for (i = 0; i < n; ++i) {
			scanf("%d:%d", &h[i], &m[i]);
			OR[0] |= sg[h[i] / 10];
			OR[1] |= sg[h[i] % 10];
			OR[2] |= sg[m[i] / 10];
			OR[3] |= sg[m[i] % 10];
		}
		printf("Case #%d:\n", k);
		h1 = 0, m1 = 0, ok = 0;
		do {
			h2 = h1, m2 = m1;
			for (i = 0; i < n; ++i) {
				if (!(cb(h[i] / 10, h2 / 10, 0) && cb(h[i] % 10, h2 % 10, 1) &&
					  cb(m[i] / 10, m2 / 10, 2) && cb(m[i] % 10, m2 % 10, 3)))
					goto lb;
				m2 = (m2 + 1) % 60;
				h2 = m2 ? h2 : (h2 + 1) % 24;
			}
			ok = 1;
			printf("%02d:%02d\n", h1, m1);
		lb:
			m1 = (m1 + 1) % 60;
			h1 = m1 ? h1 : (h1 + 1) % 24;
		} while (!(h1 == 0 && m1 == 0));
		if (!ok) printf("none\n");
	}
}