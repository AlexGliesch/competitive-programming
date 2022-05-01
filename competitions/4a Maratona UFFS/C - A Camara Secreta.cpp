#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <ciso646>
#include <cstring>
#define MOD(x) ((x) % ((ll)pow(10LL, 9LL)+7LL))

using namespace std;
typedef long long ll;

ll dp[2510][2510];

ll binom(ll n, ll k) {
	if (k == 0 or k == n) return 1;
	if (dp[n][k] == -1) {
		dp[n][k] = binom(n - 1, k - 1) + binom(n - 1, k);
		dp[n][k] = MOD(dp[n][k]);
	}
	return dp[n][k];
}

int main() {
	ll N, M; cin >> N >> M;
	vector<string> g(N);
	for (ll i = 0; i < N; ++i) {
		cin >> g[i];
	}

	memset(dp, -1, sizeof dp);
	ll xa, ya, xb, yb;
	while (cin >> xa >> ya >> xb >> yb) {
		--xa, --ya, --xb, --yb;
		ll total = 0, blocks = 0;
		for (ll i = xa; i <= xb; ++i) {
			for (ll j = ya; j <= yb; ++j) {
				++total;
				if (g[i][j] == '#') ++blocks;
			}
		}
		cout << (binom(total, blocks) - 1) << endl;
	}
}