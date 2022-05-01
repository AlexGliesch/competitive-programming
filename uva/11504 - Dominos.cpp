#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* Find all SCC. After that, count how many of them have an edge outside the
 * SCC going in it.
 *
 * (I didn't understand why; got this tip from the book and it worked) */

int N, M, num_scc;
vector<vector<int>> g, g_t;
vector<int> s, comp;
vector<bool> visited;

void dfs1(int v) {
  if (visited[v])
    return;
  visited[v] = true;
  for (int i = 0; i < g[v].size(); ++i)
    dfs1(g[v][i]);
  s.push_back(v);
}

void dfs2(int v) {
  if (visited[v])
    return;
  visited[v] = true;
  comp[v] = num_scc;
  for (int i = 0; i < g_t[v].size(); ++i)
    dfs2(g_t[v][i]);
}

void kosaraju() {
  num_scc = 0;
  s.clear();
  comp.assign(N, 0);

  visited.assign(N, false);
  for (int v = 0; v < N; ++v)
    dfs1(v);

  visited.assign(N, false);
  for (int i = s.size() - 1; i >= 0; --i) {
    if (!visited[s[i]]) {
      dfs2(s[i]);
      ++num_scc;
    }
  }
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N >> M;
    g.clear();
    g.resize(N);
    g_t.clear();
    g_t.resize(N);
    visited.assign(N, false);
    for (int i = 0; i < M; ++i) {
      int x, y;
      cin >> x >> y;
      g[x - 1].push_back(y - 1);
      g_t[y - 1].push_back(x - 1);
    }

    kosaraju();

    vector<int> in(num_scc, 0);
    for (int v = 0; v < N; ++v) {
      for (int i = 0; i < g[v].size(); ++i) {
        if (comp[v] != comp[g[v][i]])
          ++in[comp[g[v][i]]];
      }
    }

    int res = 0;
    for (int i = 0; i < num_scc; ++i)
      res += in[i] == 0 ? 1 : 0;

    cout << res << endl;
  }
}
