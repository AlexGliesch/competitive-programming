#include <ciso646>
#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int n, i, j;
  while (cin >> n >> i >> j) {
    for (int k = 1; k <= n; ++k) {
      if (((i & 1) and not(j & 1) and i + 1 == j) or
          (j & 1) and not(i & 1) and j + 1 == i) {
        cout << k << endl;
        break;
      }
      if (i & 1)
        ++i;
      if (j & 1)
        ++j;
      i >>= 1, j >>= 1;
    }
  }
}