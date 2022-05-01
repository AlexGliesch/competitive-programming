#include <vector>
#include <algorithm>
#include <ciso646>
#include <iostream>

using namespace std;

/* don't print whitespace after the last number! */

int N, C, K;

int main() {
	while (true) {
		cin >> N >> C >> K;
		if (N == 0 and C == 0 and K == 0) break;

		vector<int> v(K, 0);
		for (int n = 0; n < N; ++n) {
			for (int c = 0; c < C; ++c) {
				int x; cin >> x;
				++v[x - 1];
			}
		}

		vector<int>::iterator m = min_element(v.begin(), v.end());
		vector<int> set;
		for (int i = 0; i < K; ++i) {
			if (v[i] == *m) set.push_back(i + 1);
		}
		for (int i = 0; i < set.size() - 1; ++i)
			cout << set[i] << " ";
		cout << set.back() << endl;
	}
}