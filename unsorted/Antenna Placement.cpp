#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
using vi = vector<int>;

struct hopcroft_karp_bipartite_matching {
#define INF (1 << 28)

  hopcroft_karp_bipartite_matching(int n) : n(n) {
    mate.resize(n + 1);
    dist.resize(n + 1);
    g.resize(n + 1);
  }

  /* add edge from vertex u to v (starts from 0) */
  void add_edge(int u, int v) { g[u + 1].push_back(v + 1); }

  int max_matching() {
    int ans = 0;
    fill(mate.begin(), mate.end(), 0);
    while (bfs()) {
      for (int v = 1; v <= n; ++v) {
        if (mate[v] == 0 and dfs(v))
          ++ans;
      }
    }
    return ans;
  }

private:
  vi mate, dist;
  vector<vi> g;
  int n;

  bool bfs() {
    queue<int> q;
    for (int v = 1; v <= n; ++v) {
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
};

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int h, w, stars = 0;
    cin >> h >> w;
    vector<string> v(h);
    vector<vi> index(h, vi(w, 0));

    for (int i = 0; i < h; ++i) {
      cin >> v[i];
      for (int j = 0; j < w; ++j) {
        if (v[i][j] == '*')
          index[i][j] = stars++;
      }
    }

    hopcroft_karp_bipartite_matching hk(stars);
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        if (v[i][j] == '*') {
          int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
          for (int k = 0; k < 4; ++k) {
            int ii = i + di[k], jj = j + dj[k];
            if (ii >= 0 and jj >= 0 and ii < h and jj < w and
                v[ii][jj] == '*') {
              hk.add_edge(index[i][j], index[ii][jj]);
            }
          }
        }
      }
    }

    int matching = hk.max_matching();
    cout << (stars - 2 * matching) + matching << endl;
  }
}