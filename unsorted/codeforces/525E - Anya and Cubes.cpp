#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <ciso646>

using namespace std;
using ll = long long;

/* 
 * a very hard problem.
 * 
 * the solution: split the cubes in two equal-sized halves, and, for each half, 
 * compute all possible sums of all possible subsets and ! distributions.
 * 
 * then, for each possible sum m in the first half that uses j stickers, 
 * test if S - m is in the second half using k - j stickers or less: 
 * if it is, then add to the solution the number of ways m can be achieved by 
 * the first half with j stickers times the number fo ways S - m can be achieved
 * by the second half with k - j stickers or less.
 * 
 * also, since 18! < 10^16 < 19!, you only have to calculate the factorials of
 * up to 18.
 * */

ll fact[20], a[26], n, k, S;
unordered_map<ll, ll> num_ways[2][26];

void rec(ll sum, ll used, ll cur_i, ll max_i, ll half) {
	if (cur_i == max_i and sum <= S) {
		++num_ways[half][used][sum];
		return;
	}

	if (cur_i == max_i or sum > S or used > k) 
		return;

	rec(sum + a[cur_i], used, cur_i + 1, max_i, half);
	rec(sum, used, cur_i + 1, max_i, half);
	if (a[cur_i] < 19) 
		rec(sum + fact[a[cur_i]], used + 1, cur_i + 1, max_i, half);
}

int main() {
	fact[0] = 1;
	for (ll i = 1; i < 19; ++i) 
		fact[i] = i * fact[i - 1];

	cin >> n >> k >> S;
	for (ll i = 0; i < n; ++i) cin >> a[i];	

	rec(0, 0, 0, n / 2, 0);
	rec(0, 0, n / 2, n, 1);

	ll ans = 0;
	for (ll i = 0; i <= k; ++i) {
		for (const auto& p : num_ways[0][i]) {
			for (ll j = 0; j <= k - i; ++j) {
				if (num_ways[1][j].count(S - p.first))
					ans += num_ways[1][j][S - p.first] * p.second;
			}
		}
	}

	cout << ans << endl;
}