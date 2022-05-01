#include <iostream>
#include <vector>
#include <algorithm>
#include <ciso646>

using namespace std;

int N, M, K, ncase = 1;
vector<int> square, words, length_count;

bool rec(int col, int words_done) {
	if (col >= M) {
		return words_done == K;
	}
	if (words_done > K) {
		return false;
	}
	for (int row = 0; row < N; ++row) {
		if (col == 0 or col > 0 and square[col - 1] != row) {
			int l1 = row, l2 = N - row - 1;
			if (l1 == l2 and length_count[l1] >= 2 or l1 != l1 and
				length_count[l1] >= 1 and length_count[l2] >= 1) {
				--length_count[l1], --length_count[l2];
				square[col] = row;
				int next_words_done = words_done + (l1 * l2 == 0 ? 1 : 2);
				if (rec(col + 1, next_words_done)) return true;
				++length_count[l1], ++length_count[l2];
			}
		}
	}
	return false;
}

int main() {
	while (cin >> N >> M >> K, N and M and K) {
		length_count.clear(); length_count.resize(N, 0);
		words.clear(); words.resize(K, 0);
		square.clear(); square.resize(M, -1);
		length_count[0] = (1 << 28);

		for (int i = 0; i < K; ++i) {
			cin >> words[i];
			++length_count[words[i]];
		}
		cout << '#' << ncase++ << endl;
		if (rec(0, 0) == false) cout << 0 << endl;
		else {
			for (int i = 0; i < M; ++i)
				cout << square[i] << ' ' << i + 1 << endl;
		}
	}
}