#include <iostream>
#include <cstring>

using namespace std;

/* 
 * very simple problem. just store in an int array the maximum size of the 
 * sticks for a given column. when the stick ends (either by a 0 or end 
 * of input), if its size is greater than C, then add one to the final answer.
 * */

int main(){
	int p, n, c, maxx[1010];
	while (cin >> p >> n >> c) {
		if (p == 0 and n == 0 and c == 0) break;
		memset(maxx, 0, sizeof(maxx));
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < p; ++j) {
				int x; cin >> x;
				if (x == 0) {
					if (maxx[j] >= c) ++ans;
					maxx[j] = 0;
				} else {
					++maxx[j];
				}
			}
		}

		for (int j = 0; j < p; ++j) {
			if (maxx[j] >= c) ++ans;
		}
		cout << ans << endl;
	}
}