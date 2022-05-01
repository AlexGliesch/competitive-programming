#include <ciso646>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#define INF (1 << 30)

using namespace std;

using iii = tuple<int, int, int>;
vector<vector<int>> g;
int R, C;
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

int dijkstra() {
  priority_queue<iii, vector<iii>, greater<iii>> pq;
  vector<vector<int>> dist(R, vector<int>(C, INF));
  pq.emplace(g[0][0], 0, 0);
  dist[0][0] = g[0][0];
  while (pq.size()) {
    auto v = pq.top();
    pq.pop();
    int w = get<0>(v), r = get<1>(v), c = get<2>(v);

    if (dist[r][c] != w)
      continue;
    ;
    if (r == R - 1 and c == C - 1)
      return w;
    for (int i = 0; i < 4; ++i) {
      int cr = r + dr[i], cc = c + dc[i];
      if (cr < 0 or cr >= R)
        continue;
      if (cc < 0 or cc >= C)
        continue;
      if (dist[cr][cc] > w + g[cr][cc])
        pq.emplace(dist[cr][cc] = w + g[cr][cc], cr, cc);
    }
  }
  return INF;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> R >> C;
    g.clear();
    g.resize(R, vector<int>(C));
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        cin >> g[r][c];
      }
    }
    cout << dijkstra() << endl;
  }
}