#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int start = 0, n, best = 0;
    cin >> n;
    map<int, int> m;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      if (m.count(x) && m[x] >= start) {
        start = m[x] + 1;
      }
      m[x] = i;
      best = max(best, i - start);
    }
    cout << best + 1 << endl;
  }
}