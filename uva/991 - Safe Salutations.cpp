#include <cmath>
#include <iostream>

using namespace std;
using ll = long long;

/*
* just print the Catalan numbers.
*/

ll binom(ll n, ll k) {
  ll ans = 1;
  if (k > n - k)
    k = n - k;
  for (ll i = 0; i < k; ++i) {
    ans *= (n - i);
    ans /= (i + 1);
  }
  return ans;
}

ll catalan(ll n) {
  ll c = binom(2 * n, n);
  return c / (n + 1);
}

int main() {
  ll n, first = 0;
  while (cin >> n) {
    if (first++)
      cout << endl;
    cout << catalan(n) << endl;
  }
}