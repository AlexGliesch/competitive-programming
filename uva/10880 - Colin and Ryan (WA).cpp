#include <ciso646>
#include <cmath>
#include <iostream>
#include <set>

/*
 * Tried several times but still WA. No idea what is wrong.
 *
 * Don't forget that Q > R, and that you should not print trailing spaces.
 * Also when C = R the result is 0.
 * */

typedef long long ll;
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    if (t != 1)
      cout << endl;
    ll C, R;
    cin >> C >> R;
    cout << "Case #" << t << ": ";
    if (C == R) {
      cout << 0;
      continue;
    }

    set<ll> s;
    for (ll i = 1; i <= sqrt(C - R) + 1; ++i) {
      if ((C - R) % i == 0) {
        if (i > R)
          s.insert(i);
        if ((C - R) / i > R)
          s.insert((C - R) / i);
      }
    }

    if (s.size()) {
      cout << *begin(s);
      for (auto i = next(begin(s)); i != end(s); ++i)
        cout << " " << *i;
    }
  }
}
