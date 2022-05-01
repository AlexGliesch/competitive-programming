#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int price[13], store[13], g_big[51][51], g[13][13], dp[13][1 << 13];
int n, m, p;

int tsp(int v, int visited) {
  if (dp[v][visited] != -1)
    return dp[v][visited];
  if (visited == (1 << p) - 1)
    return dp[v][visited] = -g[v][0];
  int best = -g[v][0];
  for (int i = 0; i < p; ++i) {
    if (i != v and not(visited & (1 << i))) {
      best = max(best, -g[v][i] + price[i] + tsp(i, (visited | (1 << i))));
    }
  }
  return dp[v][visited] = best;
}

int main() {
  int T;
  cin >> T;
  cout << setprecision(2) << fixed;
  while (T--) {
    cin >> n >> m;
    ++n;
    memset(g_big, 5, sizeof g_big);
    for (int i = 0; i < m; ++i) {
      int x, y;
      double w;
      cin >> x >> y >> w;
      g_big[x][y] = g_big[y][x] = min(g_big[y][x], int(w * 10000.0));
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          g_big[i][j] = min(g_big[i][j], g_big[i][k] + g_big[k][j]);

    cin >> p;
    ++p;
    memset(g, 0, sizeof g);
    store[0] = 0, price[0] = 0;
    for (int i = 1; i < p; ++i) {
      double w;
      cin >> store[i] >> w;
      price[i] = int(w * 10000.0);
    }
    for (int i = 0; i < p; ++i) {
      g[i][i] = 0;
      for (int j = i + 1; j < p; ++j)
        g[i][j] = g[j][i] = g_big[store[i]][store[j]];
    }

    memset(dp, -1, sizeof dp);
    double val = tsp(0, 1);
    if (val <= 0)
      cout << "Don't leave the house" << endl;
    else
      cout << "Daniel can save $" << double(val / 10000.0) << endl;
  }
}