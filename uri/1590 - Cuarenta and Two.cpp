#include <iostream>
#include <algorithm>

using namespace std;

/* I was for a long time trying to find a dp solution, but, in the end, complete
 * search worked... search space was very small, I guess. */

int num[35], N, K;

int find_best(int i, int k, int best) {
	if (k == 0) return best;
	if (i >= N) return -1;
	return max(find_best(i + 1, k, best),
			   find_best(i + 1, k - 1, best & num[i]));
}

int main() {
	ios_base::sync_with_stdio(false);
	int T; cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> N >> K;
		for (int j = 0; j < N; ++j)
			cin >> num[j];
		cout << find_best(0, K, -1) << endl;
	}
}