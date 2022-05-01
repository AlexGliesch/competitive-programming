#include <algorithm>
#include <ciso646>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define INF (1 << 30)

using namespace std;
using ii = pair<int, int>;

/* Basta fazer dijkstra no grafo inverso, guardando o vetor dist.
 * Quando terminar, itera sobre dist e vê quantos valores <= E existem.
 * Note não printar linha em branco no fim. */

vector<vector<ii>> g;
int n, m, s, timer, succeeded;
vector<int> dist;

int dijkstra() {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  pq.emplace(0, s - 1);
  dist[s - 1] = 0;
  while (pq.size()) {
    int v = pq.top().second, w = pq.top().first;
    pq.pop();
    if (dist[v] != w)
      continue;
    for (const auto &e : g[v]) {
      int u = e.first, d = e.second + w;
      if (dist[u] > d) {
        pq.emplace(dist[u] = d, u);
      }
    }
  }
  return INF;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;
    cin >> n >> s >> timer >> m;
    g.clear();
    g.resize(n);
    dist.assign(n, INF);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g[v - 1].emplace_back(u - 1, w);
    }
    dijkstra();
    succeeded = 0;
    for (auto &d : dist)
      if (d <= timer)
        ++succeeded;
    cout << succeeded << endl;
  }
}