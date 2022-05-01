#include <iostream>
#include <string>

using namespace std;
using ll = long long;

int main() {
  string s;
  while (cin >> s, s != "0") {
    ll ans = 0;
    for (ll i = s.size() - 1, j = 1; i >= 0; --i, ++j) {
      ans += ll(s[i] - '0') * ll((1LL << j) - 1LL);
    }
    cout << ans << endl;
  }
}
