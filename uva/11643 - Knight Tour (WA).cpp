#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

using ii = pair<int, int>;

int dr[] = {1, 1, -1, -1, 2, 2, -2, -2}, dc[] = {2, -2, 2, -2, 1, -1, 1, -1};
int N, K, dist_large[1010][1010], dist_small[1010][1010], visited[1010][1010];
int x[16], y[16], g[16][16], dp[16][1 << 16], bfs_counter = 1;

void bfs_large(int sr, int sc) {
  memset(visited, 0, sizeof visited);
  queue<ii> q;
  q.push({sr, sc});
  dist_large[sr][sc] = 0;
  visited[sr][sc] = bfs_counter;

  while (q.size()) {
    int r = q.front().first, c = q.front().second;
    q.pop();
    for (int i = 0; i < 8; ++i) {
      int cr = r + dr[i], cc = c + dc[i];
      if (cr < 0 or cr >= 1010 or cc < 0 or cc >= 1010)
        continue;
      if (visited[cr][cc] != bfs_counter) {
        visited[cr][cc] = bfs_counter;
        dist_large[cr][cc] = dist_large[r][c] + 1;
        q.push({cr, cc});
      }
    }
  }
}

int bfs_small(int sr, int sc, int tr, int tc) {
  queue<ii> q;
  ++bfs_counter;
  q.push({sr, sc});
  dist_small[sr][sc] = 0;
  visited[sr][sc] = bfs_counter;

  while (q.size()) {
    int r = q.front().first, c = q.front().second;
    q.pop();
    if (r == tr and c == tc)
      break;
    // if (dist_small[r][c] > 30) continue;
    for (int i = 0; i < 8; ++i) {
      int cr = r + dr[i], cc = c + dc[i];
      if (cr < 0 or cr >= 1010 or cc < 0 or cc >= 1010)
        continue;
      if (visited[cr][cc] != bfs_counter) {
        visited[cr][cc] = bfs_counter;
        dist_small[cr][cc] = dist_small[r][c] + 1;
        q.push({cr, cc});
      }
    }
  }
  return dist_small[tr][tc];
}

int tsp(int v, int visited) {
  if (dp[v][visited] != -1)
    return dp[v][visited];
  if (visited == (1 << K) - 1)
    return dp[v][visited] = g[v][0];
  int best = (1 << 28);
  for (int i = 0; i < K; ++i) {
    if (i != v and not(visited & (1 << i))) {
      best = min(best, g[v][i] + tsp(i, (visited | (1 << i))));
    }
  }
  return dp[v][visited] = best;
}

int main() {
  bfs_large(0, 0);
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N >> K;
    for (int k = 0; k < K; ++k) {
      cin >> x[k] >> y[k];
      --x[k], --y[k];
    }

    for (int i = 0; i < K; ++i) {
      g[i][i] = 0;
      for (int j = i + 1; j < K; ++j) {
        if (abs(x[i] - x[j]) + abs(y[i] - y[j]) > 20 /*false*/)
          g[i][j] = g[j][i] = dist_large[abs(x[i] - x[j])][abs(y[i] - y[j])];
        else
          g[i][j] = g[j][i] = bfs_small(x[i], y[i], x[j], y[j]);
      }
    }

    memset(dp, -1, sizeof dp);
    cout << "Case " << t + 1 << ": " << tsp(0, 1) << endl;
  }
}