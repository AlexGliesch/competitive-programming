#include <algorithm>
#include <iostream>

using namespace std;

/* TLE.
 *
 * i saw it on the internet that it can be solved with merge sort, but don't
 * know why. */

int v[1000000], n;

int main() {
  while (cin >> n) {
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    int res = 0, new_n = 0;
    do {
      new_n = 0;
      for (int i = 1; i < n; ++i)
        if (v[i] < v[i - 1]) {
          swap(v[i], v[i - 1]);
          ++res, new_n = i;
        }
      n = new_n;
    } while (n != 0);
    cout << res << endl;
  }
}