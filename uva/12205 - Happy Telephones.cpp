#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int N, M, dummy;
  while (cin >> N >> M, N + M) {
    vector<int> start(N), end(N);
    for (int i = 0; i < N; ++i) {
      cin >> dummy >> dummy >> start[i] >> end[i];
      end[i] += start[i];
    }
    for (int i = 0; i < M; ++i) {
      int h, l, ans = 0;
      cin >> l >> h;
      h += l;
      for (int j = 0; j < N; ++j) {
        if (l < end[j] and h > start[j])
          ++ans;
      }
      cout << ans << endl;
    }
  }
}