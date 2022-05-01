#include <ciso646>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

/* 
 * generate a graph from mobile keyboard. start a dfs from every key, 
 * adding to the current visiting sequence the numbers as they are visited. 
 * 
 * create a function to compute the "sum" value of a given integer sequence, 
 * considering the D. this is the tricky part.
 * 
 * at the beginning of every dfs, check if the "sum" of the current sequence
 * is S; if so, add the current sequence to the list of solutions. if the sum
 * is greater than S, we can stop the dfs. however, note that if the sum is 
 * exactly S, we have to continue, in case we hit a 0!
 * 
 * don't forget to sort the list of solutions lexicografically before 
 * printing it.
 * 
 * USE LONG LONG!
 * */

vector<vector<ll>> g = {
		{ 7, 8, 9 },
		{ 2, 4, 5 },
		{ 1, 3, 4, 5, 6 },
		{ 2, 5, 6 },
		{ 1, 2, 5, 7, 8 },
		{ 1, 2, 3, 4, 6, 7, 8, 9 },
		{ 2, 3, 5, 8, 9 },
		{ 0, 4, 5, 8 },
		{ 0, 4, 5, 6, 7, 9 },
		{ 0, 5, 6, 8 }
};

ll D, S, t = 1;
vector<vector<ll>> found;

ll get_sum(const vector<ll>& x) {
	ll sum = 0, i = 0, lim = D * (ll((x.size() - 1) / D)) - 1;
	for (ll k = lim; k >= 0; --k) {
		sum += x[k] * pow(10, i++);
		if (i == D) i = 0;
	}
	for (ll k = x.size() - 1, i = 0; k > lim; --k) {
		sum += x[k] * pow(10, i++);
	}
	return sum;
}

void get_all_paths(ll visited, ll v, vector<ll> x) {
	ll sum = get_sum(x);
	if (sum > S) return;
	if (sum == S) {
		found.push_back(x);
	}
	for (auto u : g[v]) {
		if (not(visited & (1 << u))) {
			auto y = x;
			y.push_back(u);
			get_all_paths(visited | (1 << u), u, move(y));
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> S >> D) {
		if (S == -1 and D == -1) break;
		cout << "#" << t++ << endl;
		found.clear();
		for (ll i = 0; i <= 9; ++i) get_all_paths(1 << i, i, vector<ll>(1, i));

		if (found.empty()) cout << "impossivel" << endl;
		else {
			sort(found.begin(), found.end());
			for (auto& x : found) {
				for (ll k = 0; k < x.size(); ++k) {
					cout << x[k];
					if ((k + 1) % D == 0 and k != x.size() - 1) cout << " ";
				}
				cout << endl;
			}
		}
	}
}