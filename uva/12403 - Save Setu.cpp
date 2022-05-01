#include <iostream>
#include <string>

using namespace std;
using ll = long long;

/* very simple. */

int main() {
  ll t;
  cin >> t;
  ll total = 0;
  for (ll i = 0; i < t; ++i) {
    string s;
    cin >> s;
    if (s == "donate") {
      ll n;
      cin >> n;
      total += n;
    } else if (s == "report") {
      cout << total << endl;
    }
  }
}
