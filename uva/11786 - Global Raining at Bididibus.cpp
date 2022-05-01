#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int v[25000];
  int t;
  cin >> t;
  string s;
  getline(cin, s);
  while (t--) {
    int res = 0, h = 12500;
    memset(v, -1, sizeof v);
    getline(cin, s);
    for (unsigned i = 0; i < s.size(); ++i) {
      if (s[i] == '_')
        continue;
      if (s[i] == '\\') {
        v[h] = i;
        --h;
      } else {
        ++h;
        if (v[h] != -1) {
          res += i - v[h];
        }
        v[h] = -1;
      }
    }

    cout << res << endl;
  }
}