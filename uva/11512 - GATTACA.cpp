#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define MAXN 1010

using namespace std;

/*
 * once you've studied suffix arrays, the problem is quite simple.
 * to be honest, i don't understand 100% how the suffix array works, and i used
 * it as kind of a black box (code and explanation availabe in page 257 of the
 * book, 3rd edition).
 *
 * in this particular problem, you must find the longest repeating substring in
 * the given string. however, not only do you have to find it, you must find how
 * many times it occurs in that string; in order to do that, you can run kmp
 * on the input string with the lrs as pattern.
 *
 * OPTIMIZATION: i got the idea from the internet that the number of occurences
 * is equal to the number of times the maximum lcp is found in the lcp array,
 * for those indices where lcp[i] == lcp[i - 1]. i don't fully understand why,
 * but it works faster than kmp, and allowed me to get rank 1 in this problem.
 * however, i will not submit this solution because i don't understand it.
 *
 * */

struct SuffixArray {
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

  void construct_sa(const string &T) {
    t = T, n = T.size();
    for (int i = 0; i < n; ++i)
      ra[i] = t[i];
    for (int i = 0; i < n; ++i)
      sa[i] = i;
    for (int k = 1; k < n; k <<= 1) {
      counting_sort(k);
      counting_sort(0);
      int r = temp_ra[sa[0]] = 0;
      for (int i = 1; i < n; ++i) {
        temp_ra[sa[i]] =
            ((ra[sa[i]] == ra[sa[i - 1]] and ra[sa[i] + k] == ra[sa[i - 1] + k])
                 ? r
                 : ++r);
      }
      memcpy(ra, temp_ra, n * sizeof(int));
      if (ra[sa[n - 1]] == n - 1)
        break;
    }
  }

  void compute_lcp() {
    int L = 0;
    phi[sa[0]] = -1;
    for (int i = 0; i < n; ++i)
      phi[sa[i]] = sa[i - 1];
    for (int i = 0; i < n; ++i) {
      if (phi[i] == -1) {
        plcp[i] = 0;
        continue;
      }
      while (t[i + L] == t[phi[i] + L])
        L++;
      plcp[i] = L;
      L = max(L - 1, 0);
    }
    for (int i = 0; i < n; ++i)
      lcp[i] = plcp[sa[i]];
  }

  string lrs() {
    int ix = 0, max_lcp = -1;
    for (int i = 1; i < n; ++i) {
      if (lcp[i] > max_lcp)
        max_lcp = lcp[i], ix = i;
    }

    return string(t, sa[ix], max_lcp);
  }
};

int b[MAXN]; /* back table for kmp. */

void kmp_preprocess(const string &p /* pattern */) {
  int i = 0, j = -1, m = p.size();
  b[0] = -1;
  while (i < m) {
    while (j >= 0 and p[i] != p[j])
      j = b[j];
    ++i, ++j;
    b[i] = j;
  }
}

/*
 * this kmp_search will simply count the number of occurences of p in s.
 * */
int kmp_search(const string &s, const string &p) {
  int i = 0, j = 0, n = s.size(), m = p.size(), ans = 0;
  while (i < n) {
    while (j >= 0 and s[i] != p[j])
      j = b[j];
    ++i, ++j;
    if (j == m) {
      j = b[j];
      ++ans;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  int ncases;
  cin >> ncases;
  string s;
  getline(cin, s);
  SuffixArray sa;
  for (int i = 0; i < ncases; ++i) {
    getline(cin, s);
    s += '$';
    sa.construct_sa(s);
    sa.compute_lcp();

    auto x = sa.lrs();
    if (x.empty())
      cout << "No repetitions found!" << endl;
    else {
      kmp_preprocess(x);
      cout << x << ' ' << kmp_search(s, x) << endl;
    }
  }
}