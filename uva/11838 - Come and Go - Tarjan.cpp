#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int V, E;
vector<vector<int>> g;

void tarjan_dfs(int v, int &num_scc, int &ix, vector<int> &visited,
                vector<int> &index, vector<int> &low, vector<int> &s) {
  if (index[v] != -1)
    return;
  visited[v] = true;
  index[v] = low[v] = ix++;
  s.push_back(v);

  for (int i = 0; i < g[v].size(); ++i) {
    if (index[g[v][i]] == -1) {
      tarjan_dfs(g[v][i], num_scc, ix, visited, index, low, s);
      low[v] = min(low[v], low[g[v][i]]);
    } else if (visited[g[v][i]]) {
      low[v] = min(low[v], index[g[v][i]]);
    }
  }

  if (low[v] == index[v]) {
    ++num_scc;
    while (true) {
      int u = s.back();
      s.pop_back();
      visited[u] = 0;
      if (u == v)
        break;
    }
  }
}

/* returns the number of strongly connected components in g */
int tarjan_scc(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> visited(n, false), index(V, -1), low(V, 0), s;
  int ix = 0, num_scc = 0;
  for (int v = 0; v < n; ++v)
    tarjan_dfs(v, num_scc, ix, visited, index, low, s);
  return num_scc;
}

int main() {
  while (cin >> V >> E, V != 0) {
    g.clear();
    g.resize(V + 1);
    for (int i = 0; i < E; ++i) {
      int u, v, p;
      cin >> u >> v >> p;
      --u, --v;
      g[u].push_back(v);
      if (p == 2)
        g[v].push_back(u);
    }

    bool ok = (tarjan_scc(g) == 1);
    cout << (ok ? 1 : 0) << endl;
  }
}