#include <iostream>
#include <vector>

using namespace std;

int V, E;
vector<vector<int>> g, g_t;
vector<bool> visited;
vector<int> s;
int num_scc;

void dfs(int v, vector<vector<int>> &g, vector<int> *s) {
  if (visited[v])
    return;
  visited[v] = true;
  for (int i = 0; i < g[v].size(); ++i)
    dfs(g[v][i], g, s);
  if (s)
    s->push_back(v);
}

void kosaraju() {
  num_scc = 0;
  s.clear();

  visited.assign(V + 1, false);
  for (int v = 1; v <= V; ++v)
    dfs(v, g, &s);

  visited.assign(V + 1, false);
  while (s.size()) {
    int v = s.back();
    s.pop_back();
    if (!visited[v]) {
      ++num_scc;
      dfs(v, g_t, NULL);
    }
  }
}

int main() {
  while (cin >> V >> E, V != 0) {
    g.clear();
    g.resize(V + 1);
    g_t.clear();
    g_t.resize(V + 1);

    for (int i = 0; i < E; ++i) {
      int u, v, p;
      cin >> u >> v >> p;
      g[u].push_back(v);
      g_t[v].push_back(u);
      if (p == 2)
        g[v].push_back(u), g_t[u].push_back(v);
    }

    kosaraju();
    cout << (num_scc == 1 ? 1 : 0) << endl;
  }
}