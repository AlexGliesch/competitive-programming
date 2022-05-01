#include <vector>
#include <ciso646>
#include <iostream>

using namespace std;
typedef long long ll;

/* 
 * The idea: the number of swaps in bubble sort and merge sort are the
 * same. So we can run merge sort instead (because O(n^2) is too large).
 * 
 * Below is an algorithm to perform a mergesort and get the number of swaps. 
 * I don't understand why the algorithm works, I took it from the internet,
 * but it works.
 * */

ll num_swaps = 0;
vector<ll> A(100010), B(100010);

void merge(ll l, ll m, ll r) {
	ll h = l, i = l, j = m + 1;
	while (h <= m and j <= r) {
		if (A[h] < A[j]) {
			B[i++] = A[h++];
		} else {
			B[i++] = A[j++];
			num_swaps += j - i;
		}
	}

	if (h > m) {
		for (ll k = j; k <= r; ++k) B[i++] = A[k];
	} else {
		for (ll k = h; k <= m; ++k) B[i++] = A[k];
	}
	copy(B.begin() + l, B.begin() + r + 1, A.begin() + l);
}

void merge_sort(ll l, ll h) {
	if (l < h) {
		ll m = (h + l) / 2;
		merge_sort(l, m);
		merge_sort(m + 1, h);
		merge(l, m, h);
	}
}

int main() {
	ll N;
	ios_base::sync_with_stdio(false);
	while (cin >> N, N) {
		for (ll i = 0; i < N; ++i) cin >> A[i];
		num_swaps = 0;
		merge_sort(0, N - 1);
		cout << (num_swaps % 2 == 1 ? "Marcelo" : "Carlos") << endl;
	}
}