#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define LSOne(x) ((x) & (-x))

using namespace std;
using vi = vector<int>;

/* structure used to return the number of elements greater than x in a range.
 * complexity: (?)
 * note: all indices in the sqrt_decomposition class start at 1, not at 0! */
struct sqrt_decomposition {
  /* build data strucutre. u: input vector,
   * maxval: maximum possible value an element can assume (with updates) */
  sqrt_decomposition(const vi &u, int maxval)
      : block_sz(sqrt(u.size() + 10)), maxval(maxval) {
    v.assign(u.size() + 1, 0);
    t.assign((block_sz + 10) * (maxval + 10), 0);
    for (int i = 0; i < u.size(); ++i) {
      update((i + 1) / block_sz, u[i], 1);
      v[i + 1] = u[i];
    }
  }

  /* set the k-th element to val */
  void update(int k, int val) {
    update(k / block_sz, v[k], -1);
    update(k / block_sz, val, 1);
    v[k] = val;
  }

  /* returns the number of values greater than k in the range [L, R]
   * (inclusive) */
  int greater_range(int L, int R, int k) {
    int ans = 0;
    while (L <= R and L % block_sz != 0)
      ans += v[L++] > k;
    while (L <= R and R % block_sz != block_sz - 1)
      ans += v[R--] > k;
    if (L < R) {
      for (int a = L / block_sz; a <= R / block_sz; ++a)
        ans += sum(a, k + 1);
    }
    return ans;
  }

private:
  void update(int block, int k, int val) {
    while (k > 0) {
      t[block + k * block_sz] += val;
      k -= LSOne(k);
    }
  }

  int sum(int block, int k) {
    int ans = 0;
    while (k <= maxval) {
      ans += t[block + k * block_sz];
      k += LSOne(k);
    }
    return ans;
  }

  int block_sz, maxval;
  vi v, t;
};

int main() {
  ios_base::sync_with_stdio(false);
  int n, q;
  while (cin >> n) {
    vi v(n);
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    cin >> q;
    sqrt_decomposition s(v, 10000);
    for (int i = 0; i < q; ++i) {
      int flag;
      cin >> flag;
      if (flag == 0) {
        int i, v;
        cin >> i >> v;
        s.update(i, v);
      } else {
        int i, j, k;
        cin >> i >> j >> k;
        cout << s.greater_range(i, j, k) << endl;
      }
    }
  }
}