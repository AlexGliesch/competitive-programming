#include <algorithm>
#include <ciso646>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int coord[15][2], g[15][15], size[2], n, dp[11][1 << 11];

int tsp(int v, int visited) {
  if (dp[v][visited] != -1)
    return dp[v][visited];
  if (visited == (1 << n) - 1)
    return dp[v][visited] = g[v][0];
  int best = (1 << 28);
  for (int i = 0; i < n; ++i) {
    if (i != v and not(visited & (1 << i))) {
      best = min(best, g[v][i] + tsp(i, (visited | (1 << i))));
    }
  }
  return dp[v][visited] = best;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    memset(dp, -1, sizeof dp);
    cin >> size[0] >> size[1] >> coord[0][0] >> coord[0][1] >> n;
    ++n;
    for (int i = 1; i < n; ++i)
      cin >> coord[i][0] >> coord[i][1];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          g[i][j] = 0;
        } else {
          g[i][j] =
              abs(coord[i][0] - coord[j][0]) + abs(coord[i][1] - coord[j][1]);
        }
      }
    }

    cout << "The shortest path has length " << tsp(0, 1) << endl;
  }
}