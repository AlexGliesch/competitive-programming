#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define LSOne(x) (x & (-x))

using namespace std;
using vi = vector<int>;

/* important: ft starts from index 1, not index 0 !!! */
struct fenwick_tree {
  fenwick_tree(int n) { ft.assign(n + 1, 0); }
  /* returns sum of range [0, b] inclusive */
  int rsq(int b) {
    int ans = 0;
    for (; b; b -= LSOne(b))
      ans += ft[b];
    return ans;
  }
  /* adjust value of kth element by v (difference) */
  void adjust(int k, int v) {
    for (; k < ft.size(); k += LSOne(k))
      ft[k] += v;
  }

private:
  vi ft;
};

void sieve(int N, vi &ispr, vi &pr) {
  ispr.assign(N + 10, 1);
  pr.clear();
  ispr[0] = ispr[1] = 0;
  int lim = sqrt(N);
  for (int i = 2; i <= lim; ++i) {
    if (i % 10000 == 0)
      cout << i << endl;
    if (ispr[i]) {
      for (int j = i * i; j <= N; j += i) {
        ispr[j] = 0;
      }
      pr.push_back(i);
    }
  }
  for (int i = lim + 1; i <= N; ++i)
    if (ispr[i])
      pr.push_back(i);
}

int count_pf(int n, vi &pr) {
  int i = 0, pf = pr[0], ans = 0;
  while (pf * pf <= n) {
    while (n % pf == 0) {
      n /= pf;
      ++ans;
    }
    pf = pr[++i];
  }
  if (n != 1)
    ++ans;
  return ans;
}

int to7(int i) {
  string s = to_string(i);
  reverse(s.begin(), s.end());
  while (s.size() < 7)
    s.push_back('0');
  return stoi(s);
}

/* return index of first occurence of element target in sorted function (get).
 * if there is no target, returns the first before */
template <typename T, typename F>
int binary_search(int lo, int hi, const T &target, const F &get) {
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (get(mid) == target)
      return mid;
    else if (get(mid) < target)
      lo = mid + 1;
    else
      hi = mid - 1;
  }
  return hi;
}

int main() {
  vi ispr, pr, pr7;
  sieve(1000000, ispr, pr);
  fenwick_tree cum_ft(pr.size()), freq_ft(pr.size());
  for (int i = 0; i < pr.size(); ++i) {
    pr7.push_back(to7(pr[i]));
  }
  sort(pr7.begin(), pr7.end());
  vi num_pf(pr.size());
  map<int, int> index;
  for (int i = 0; i < pr.size(); ++i) {
    index[pr7[i]] = i;
    num_pf[i] = count_pf(pr7[i], pr);
  }
  for (int i = 0; i < pr.size(); ++i) {
    cum_ft.adjust(i + 1, num_pf[i]);
    freq_ft.adjust(i + 1, 1);
  }
  char q;
  int i;
  while (cin >> q >> i) {
    // 		cout<<q<<", "<<i<<endl;
    if (q == 'q') { /* query */
      /* which index has freq exactly i? */
      int j = binary_search(0, pr.size() - 1, i + 1,
                            [&](int k) { return freq_ft.rsq(k + 1); });
      cout << cum_ft.rsq(j + 1) << endl;
    } else if (q == 'd') { /* delete*/
      int j = index[i];
      cum_ft.adjust(j + 1, -num_pf[j]);
      freq_ft.adjust(j + 1, -1);
    }
  }
}