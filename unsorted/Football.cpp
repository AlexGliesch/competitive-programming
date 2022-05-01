#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, g;
  while (cin >> n >> g) {
    int p = 0;

    vector<int> diff(101, 0);
    for (int i = 0; i < n; i++) {
      int s, r;
      cin >> s >> r;
      if (s <= r)
        diff[r - s]++;
      p += (s == r) + 3 * (s > r);
    }

    p += 2 * min(g, diff[0]);
    g -= diff[0];

    for (int i = 1; i < 100 && g >= i; i++) {
      int b = i + 1;

      if (g >= b * diff[i]) {
        p += 3 * diff[i];
        g -= b * diff[i];
      } else {
        p += 3 * ((int)(g / b));
        g = g % b;
        if (g == b - 1) {
          p++;
          g -= b - 1;
        }
      }
    }

    cout << p << endl;
  }
  return 0;
}