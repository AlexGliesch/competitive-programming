#include <algorithm>
#include <bitset>
#include <iostream>

using namespace std;

bitset<1000100> s;

int main() {
  int n, m;
  while (cin >> n >> m, n + m > 0) {
    bool conflict = false;
    s.reset();
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      if (conflict)
        continue;
      for (int j = x; j < y; ++j) {
        if (s[j])
          conflict = true;
        s[j] = true;
      }
    }

    for (int i = 0; i < m; ++i) {
      int x, y, z;
      cin >> x >> y >> z;
      if (conflict)
        continue;
      int k = 0;
      while (k + x < 1000000) {
        for (int j = x + k; j < min(1000000, y + k); ++j) {
          if (s[j])
            conflict = true;
          s[j] = true;
        }
        k += z;
      }
    }

    if (!conflict)
      cout << "NO ";
    cout << "CONFLICT" << endl;
  }
}