#include <algorithm>
#include <iostream>
#include <vector>
#define LSOne(x) (x & (-x))

using namespace std;
using ll = long long;
using vi = vector<ll>;

/* important: ft starts from index 1, not index 0! */
struct fenwick_tree_range_update {
  fenwick_tree_range_update(ll n) {
    b1.assign(n + 1, 0);
    b2.assign(n + 1, 0);
  }
  /* returns sum of range [0, b] inclusive */
  ll rsq(ll b) { return rsq(b1, b) * b - rsq(b2, b); }
  /* returns sum of range [a, b] inclusive */
  ll rsq(ll i, ll j) { return rsq(j) - rsq(i - 1); }
  /* adjust value of kth element by v (difference) */
  void adjust(vi &ft, ll k, ll v) {
    for (; k < ft.size(); k += LSOne(k))
      ft[k] += v;
  }
  /* adjust values from index a to index b inclusive by v */
  void adjust(ll i, ll j, ll v) {
    adjust(b1, i, v);
    adjust(b1, j + 1, -v);
    adjust(b2, i, v * (i - 1));
    adjust(b2, j + 1, -v * j);
  }

private:
  ll rsq(vi &ft, ll b) {
    ll ans = 0;
    for (; b; b -= LSOne(b))
      ans += ft[b];
    return ans;
  }
  vi b1, b2;
};

int main() {
  ll t;
  cin >> t;
  for (ll i = 0; i < t; ++i) {
    ll n, c;
    cin >> n >> c;
    fenwick_tree_range_update ft(n);
    for (ll j = 0; j < c; ++j) {
      ll op;
      cin >> op;
      if (op == 0) {
        ll p, q, v;
        cin >> p >> q >> v;
        ft.adjust(p, q, v);
      } else {
        ll p, q;
        cin >> p >> q;
        cout << ft.rsq(p, q) << endl;
      }
    }
  }
}