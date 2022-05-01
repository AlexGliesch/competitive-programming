#include <iostream>
#include <ciso646>
#include <cstring>

/*
 * For every height, count how many 'holes' in it. O(n^2) works.
 **/

using namespace std;

int main() {
	int A, C, h[10010], last_block[10010];
	while (cin >> A >> C, A or C) {
		for (int i = 0; i < C; ++i)cin >> h[i];
		memset(last_block, -1, sizeof last_block);

		int ans = 0;
		for (int i = 0; i < C; ++i) {
			for (int j = h[i]; j >= 1; --j) {
				if (i - last_block[j] > 1) {
					++ans;
				}
				last_block[j] = i;
			}
		}

		for (int j = A; j >= 1; --j) {
			if (C - last_block[j] > 1) {
				++ans;
			}
		}
		cout << ans << endl;
	}	
}