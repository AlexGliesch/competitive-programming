#include <vector>
#include <iostream>
#include <ciso646>

using namespace std;

int main() {
	int N;
	while (cin >> N, N) {
		vector<int> v(N);
		for (int i = 0; i < N; ++i) cin >> v[i];
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			int bef = (i == 0 ? N - 1 : i - 1);
			int aft = (i == N - 1 ? 0 : i + 1);
			if (v[i] < v[bef] and v[i] < v[aft] or
				v[i] > v[bef] and v[i] > v[aft]) {
				++ans;
			}
		}
		cout << ans << endl;
	}
}