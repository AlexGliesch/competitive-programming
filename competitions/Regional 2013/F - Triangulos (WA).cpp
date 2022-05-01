#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;

bitset<100000010> has;
int starts[100010];

int main() {
	int n; 
	while (cin >> n) {
		int tl = 0;
		has.reset();
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			has[x + tl] = true;
			starts[i] = x + tl;
			tl += x;
		}
		if (tl % 3 != 0) {
			cout << 0 << endl;
		} else {
			int ans = 0;
			for (int i = 0; i < n; ++i) {
				int x = starts[i];
				if (has[(x + tl / 3) % tl] and has[(x + 2 * (tl / 3)) % tl])
					++ans;
			}
			cout << ans / 3 << endl;
		}
	}
}
