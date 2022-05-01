#include <algorithm>
#include <ciso646>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

/*
 * we just need to run dijkstra's shortest paths, nothing else.
 * if you need help with dijkstra's, consult your book.
 * */

vector<vector<pair<int, int>>> g;
vector<int> dist;
int n, m, s, t;

int dijkstra() {
  priority_queue<pair<int, int>> pq;
  pq.emplace(0, s);
  dist[s] = 0;
  while (pq.size()) {
    int v = pq.top().second, w = -pq.top().first;
    pq.pop();
    if (dist[v] != w)
      continue;
    if (v == t)
      return w;
    for (const auto &e : g[v]) {
      int u = e.first, d = e.second + w;
      if (dist[u] > d) {
        pq.emplace(-(dist[u] = d), u);
      }
    }
  }
  return numeric_limits<int>::max();
}

int main() {
  ios_base::sync_with_stdio(false);
  int N;
  cin >> N;
  for (int ncase = 1; ncase <= N; ++ncase) {
    cin >> n >> m >> s >> t;
    g.clear();
    g.resize(n);
    dist.assign(n, numeric_limits<int>::max());
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
    int ans = dijkstra();
    cout << "Case #" << ncase << ": ";
    if (ans == numeric_limits<int>::max())
      cout << "unreachable" << endl;
    else
      cout << ans << endl;
  }
}