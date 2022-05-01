#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>
#define INF (1 << 30)

using namespace std;

/* Simple problem, just check for every hotels that have more than N rooms
 * available for a certain week, the one that has the least p * N. If it's
 * greater than B, then no. */

int main() {
  ios_base::sync_with_stdio(false);
  int N, B, H, W;
  while (cin >> N >> B >> H >> W) {
    int m = INF;
    for (int i = 0; i < H; ++i) {
      int p;
      cin >> p;
      vector<int> a(W);
      for (int j = 0; j < W; ++j)
        cin >> a[j];
      if (any_of(begin(a), end(a), [=](int x) { return x >= N; }))
        m = min(m, p * N);
    }
    if (m == INF or m > B)
      cout << "stay home" << endl;
    else
      cout << m << endl;
  }
}