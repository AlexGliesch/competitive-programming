#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;

unordered_map<char, int> m = {{'B', 1},      {'U', 10},    {'S', 100},
                              {'P', 1000},   {'F', 10000}, {'T', 100000},
                              {'M', 1000000}};

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    unordered_map<char, int> count;
    string s;
    cin >> s;
    ll ans = 0, last = 0;
    ll order = 0;
    bool ok = true;
    for (int j = 0; j < s.size(); ++j) {
      ll x = m[s[j]];
      if (j != 0 and x != last) {
        if (order == 0)
          if (x < last)
            order = -1;
          else
            order = 1;
        else if (order == -1 and x > last) {
          ok = false;
          break;
        } else if (order == 1 and x < last) {
          ok = false;
          break;
        }
      }
      ans += x;
      ++count[s[j]];
      last = x;
    }
    for (auto &p : count)
      if (p.second > 9)
        ok = false;
    if (not ok)
      cout << "error" << endl;
    else
      cout << ans << endl;
  }
}
