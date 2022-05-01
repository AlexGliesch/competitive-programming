#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int n, m, m2, l[2], r[2], p[14][2];

bool backtrack(int pos, int last, int used) {
  if (pos == n)
    return last == r[0];
  for (int j = 0; j < m; ++j) {
    if (used & (1 << j))
      continue;
    if (last == p[j][0]) {
      if (backtrack(pos + 1, p[j][1], used | (1 << j)))
        return true;
    } else if (last == p[j][1]) {
      if (backtrack(pos + 1, p[j][0], used | (1 << j)))
        return true;
    }
  }
  return false;
}

int main() {
  while (cin >> n >> m, n != 0) {
    cin >> l[0] >> l[1] >> r[0] >> r[1];
    for (int i = 0; i < m; ++i) {
      cin >> p[i][0] >> p[i][1];
    }
    cout << (backtrack(1, l[1], 0) ? "YES" : "NO") << endl;
  }
}