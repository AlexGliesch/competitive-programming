#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int cycle_length(int n) {
  int len = 1;
  while (n != 1) {
    if (n & 1)
      n = n + n + n + 1;
    else
      n = (n >> 1);
    ++len;
  }
  return len;
}

int main() {
  ios_base::sync_with_stdio(false);
  vector<int> len(1000005, -1);

  int x, y;
  while (cin >> x >> y) {
    int m = 0;
    for (int i = min(x, y); i <= max(x, y); ++i) {
      if (len[i] == -1)
        len[i] = cycle_length(i);
      m = max(m, len[i]);
    }
    cout << x << ' ' << y << ' ' << m << endl;
  }
}