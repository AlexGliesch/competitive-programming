#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define INF (1 << 28)
#define MAX_V 500

using namespace std;

/* Pode-se enxergar as cartas azuis e vermelhas são duas bipartições de um
* grafo. Colocando as arestas como os pares de cartas que dão resposta ímpar,
* o emparelhamento máximo é o máximo que o John ganha, logo Mary ganhará
* no mínimo N menos isso. */

int n;
vector<vector<int>> g;

struct HopcroftKarp {
  int mate[MAX_V], dist[MAX_V];

  bool bfs() {
    queue<int> q;
    for (int v = 1; v <= 2 * n; ++v) {
      if (mate[v] == 0) {
        dist[v] = 0;
        q.push(v);
      } else
        dist[v] = INF;
    }
    dist[0] = INF;
    while (q.size()) {
      int u = q.front();
      q.pop();
      if (u == 0)
        continue;
      for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (dist[mate[v]] == INF) {
          dist[mate[v]] = dist[u] + 1;
          q.push(mate[v]);
        }
      }
    }
    return dist[0] != INF;
  }

  bool dfs(int u) {
    if (u == 0)
      return true;
    for (int i = 0; i < g[u].size(); ++i) {
      int v = g[u][i];
      if (dist[mate[v]] == dist[u] + 1 and dfs(mate[v])) {
        mate[u] = v;
        mate[v] = u;
        return true;
      }
    }
    dist[u] = INF;
    return false;
  }

  /* IMPORTANT: indices in g must start from 1, not from 0! */
  int bipartite_matching(const vector<vector<int>> &g) {
    int max_matching = 0;
    memset(mate, 0, sizeof mate);
    while (bfs()) {
      for (int v = 1; v <= 2 * n; ++v) {
        if (mate[v] == 0 and dfs(v))
          ++max_matching;
      }
    }
    return max_matching;
  }
};

int main() {
  while (cin >> n, n) {
    vector<int> v1(n + 1), v2(n + 1);
    for (int i = 1; i <= n; ++i)
      cin >> v1[i];
    for (int i = 1; i <= n; ++i)
      cin >> v2[i];

    g.clear();
    g.resize(2 * (n + 1));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if ((v1[i] + v2[j]) % 2 != 0) {
          g[i].push_back(j + n);
          g[j + n].push_back(i);
        }
      }
    }
    HopcroftKarp hk;
    cout << n - hk.bipartite_matching(g) << endl;
  }
}