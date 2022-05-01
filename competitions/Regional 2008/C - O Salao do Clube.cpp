#include <iostream>
#include <map>
#include <algorithm>
#include <ciso646>
#define INF (1<<28)

using namespace std;

/* 
 * Use the fact that there are at most 2 planks in a given row. First, try
 * to fill the most rows you can with 1 plank, then, for every length X of all
 * given plank lengths, try to fill it with two planks of length X and X - H,
 * as long as there are enough planks available with those lengths.
 * 
 * Here, H is either M/L and N/L, as you try to fill the floor with both
 * orientations. If either M/L or N/L is not an exact division, you discard it.
 * If both M/L and N/L are not exact divisions, its impossible.
 * 
 * Keep map<int, int> that tells the number of planks available of each length.

 * */

int min_planks(int L, int count, map<int, int> len_ct) {
	int num = min(count, len_ct[L]);
	int ans = num;
	count -= num;
	len_ct[L] -= num;

	for (map<int, int>::iterator i = len_ct.begin(); i != len_ct.end(); ++i) {
		if (count == 0) break;
		int P1 = i->first;
		int P2 = L - i->first;
		if (P1 >= L) continue;

		num = P1 != P2 ? min(len_ct[P1], len_ct[P2]) : len_ct[P1] / 2;
		num = min(num, count);
		ans += 2 * num;
		count -= num;
		len_ct[P1] -= num;
		len_ct[P2] -= num;
	}
	return (count == 0 ? ans : INF);
}

int main() {
	ios_base::sync_with_stdio(false);
	int M, N, L, K;
	while (cin >> M >> N, M or N) {
		M *= 100, N *= 100;
		cin >> L >> K;
		map<int, int> len_count;
		for (int i = 0; i < K; ++i) {
			int Ki; cin >> Ki;
			len_count[Ki * 100]++;
		}

		int ans = INF;
		if (M % L == 0) {
			ans = min(ans, min_planks(N, M / L, len_count));
		}
		if (N % L == 0) {
			ans = min(ans, min_planks(M, N / L, len_count));
		}

		if (ans == INF) {
			cout << "impossivel" << endl;
		} else {
			cout << ans << endl;
		}
	}
}