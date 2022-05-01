#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* very easy. the stupidest brute force solution works, since <= 100. */

int n, v[101][101];

bool has_parity() {
  for (int i = 0; i < n; ++i) {
    int count_row = 0, count_col = 0;
    for (int j = 0; j < n; ++j) {
      count_col += v[i][j];
      count_row += v[j][i];
    }
    if (count_row & 1 or count_col & 1)
      return false;
  }
  return true;
}

int main() {
  while (cin >> n, n) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        cin >> v[i][j];

    if (has_parity())
      cout << "OK" << endl;
    else {
      bool found = false;
      for (int i = 0; i < n and not found; ++i) {
        for (int j = 0; j < n and not found; ++j) {
          v[i][j] = not v[i][j];
          if (has_parity()) {
            found = true;
            cout << "Change bit (" << i + 1 << "," << j + 1 << ")" << endl;
          }
          v[i][j] = not v[i][j];
        }
      }
      if (not found)
        cout << "Corrupt" << endl;
    }
  }
}