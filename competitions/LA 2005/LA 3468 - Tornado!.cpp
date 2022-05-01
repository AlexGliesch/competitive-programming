#include <iostream>
#include <vector>
#include <ciso646>
#include <cmath>
#include <numeric>

using namespace std;

int n;
int Prev(int i) { return i == 0 ? n - 1 : i - 1; }
int Next(int i) { return (i + 1) % n; }

int main() {
	while (cin >> n, n != 0) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];

		if (accumulate(v.begin(), v.end(), 0) == 0) {
			cout << (int)ceil(n / 2.0) << endl;
			continue;
		}

		int r = 0;
		bool found = true;

		while (found) {
			found = false;
			for (int i = 0; i < n; ++i) {
				int pr = Prev(i), nx = Next(i);			
				if (v[i] == 0) {
					found = true;
					if (v[i] + v[pr] + v[nx] == 2) { /* 1 0 1 */
						v[i] = 1;
					} else if (v[pr] == 0 and v[Prev(pr)] == 1) { /* 1 0 0 */
						v[i] = v[pr] = 1; ++r;
					} else if (v[nx] == 0 and v[Next(nx)] == 1) { /* 0 0 1 */
						v[i] = v[nx] = 1; ++r;
					}
				}
			}
		}

		cout << r << endl;
	}

}