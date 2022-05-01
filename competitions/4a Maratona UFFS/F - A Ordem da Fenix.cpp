#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ciso646>
#include <cstring>
#define MAXN 100010

using namespace std;

struct SuffixArray {
public:
	/*
	 * build a suffix array
	 * */
	void build(const string& T) {
		construct_sa(T);
		compute_lcp();
	}

	/*
	* returns the longest repeated substring. if there are more than one,
	* returns the one which compares lexicografically less.
	* */
	string lrs() {
		int ix = 0, max_lcp = -1;
		string ans;
		for (int i = 1; i < n; ++i) {
			if (lcp[i] > max_lcp or
				(lcp[i] == max_lcp and string(t, sa[i], lcp[i]) < ans)) {
				max_lcp = lcp[i], ix = i;
				ans = string(t, sa[i], lcp[i]);
			}
		}

		return string(t, sa[ix], max_lcp);
	}

private:

	int n, sa[MAXN], temp_sa[MAXN], ra[MAXN], temp_ra[MAXN];
	int lcp[MAXN], c[MAXN], plcp[MAXN], phi[MAXN];
	string t;

	void counting_sort(int k) {
		int maxi = max(300, n), sum = 0;
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; ++i)
			c[i + k < n ? ra[i + k] : 0]++;
		for (int i = 0; i < maxi; ++i) {
			int t = c[i];
			c[i] = sum;
			sum += t;
		}
		for (int i = 0; i < n; ++i)
			temp_sa[c[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];
		memcpy(sa, temp_sa, n * sizeof(int));
	}

	void construct_sa(const string& T) {
		t = T, n = T.size();
		for (int i = 0; i < n; ++i) ra[i] = t[i];
		for (int i = 0; i < n; ++i) sa[i] = i;
		for (int k = 1; k < n; k <<= 1) {
			counting_sort(k);
			counting_sort(0);
			int r = temp_ra[sa[0]] = 0;
			for (int i = 1; i < n; ++i) {
				temp_ra[sa[i]] = ((ra[sa[i]] == ra[sa[i - 1]] and
					ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r);
			}
			memcpy(ra, temp_ra, n * sizeof(int));
			if (ra[sa[n - 1]] == n - 1) break;
		}
	}

	void compute_lcp() {
		int L = 0;
		phi[sa[0]] = -1;
		for (int i = 0; i < n; ++i) phi[sa[i]] = sa[i - 1];
		for (int i = 0; i < n; ++i) {
			if (phi[i] == -1) {
				plcp[i] = 0;
				continue;
			}
			while (t[i + L] == t[phi[i] + L]) L++;
			plcp[i] = L;
			L = max(L - 1, 0);
		}
		for (int i = 0; i < n; ++i) lcp[i] = plcp[sa[i]];
	}
} sa;

int main() {
	ios_base::sync_with_stdio(false);
	string s; cin >> s;
	sa.build(s);
	string lrs = sa.lrs();
	cout << (lrs.size() >= 3 ? lrs : "*") << endl;
}
