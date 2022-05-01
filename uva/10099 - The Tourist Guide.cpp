#include <algorithm>
#include <ciso646>
#include <functional>
#include <iostream>
#include <vector>

/* Minimax normal. Sacada: o motorista conta como passageiro, logo o
 * número máximo de passageiros é o bottleneck do grafo menos 1! */

using namespace std;

int n, m, s, d, t, max_passengers, scenario = 0;
vector<tuple<int, int, int>> g;
vector<vector<pair<int, int>>> dag;
vector<int> pset;
vector<bool> visited;

void init_set(int n) {
  pset.assign(n, 0);
  for (int i = 0; i < n; ++i)
    pset[i] = i;
}

int find_set(int i) { return pset[i] == i ? i : (pset[i] = find_set(pset[i])); }

bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

void union_set(int i, int j) {
  if (is_same_set(i, j))
    return;
  pset[find_set(i)] = find_set(j);
}

bool dfs(int v) {
  if (visited[v])
    return false;
  if (v == d)
    return true;
  visited[v] = true;
  for (auto &e : dag[v]) {
    if (dfs(e.first)) {
      max_passengers = min(max_passengers, e.second);
      return true;
    }
  }
  return false;
}

int main() {
  while (cin >> n >> m, n and m) {
    g.clear();
    g.resize(m);
    dag.clear();
    dag.resize(n);

    for (int i = 0; i < m; ++i) {
      cin >> get<1>(g[i]) >> get<2>(g[i]) >> get<0>(g[i]);
      --get<1>(g[i]), --get<2>(g[i]);
    }
    cin >> s >> d >> t;
    --s, --d;

    sort(begin(g), end(g));
    init_set(n);

    for (int i = m - 1; i >= 0; --i) {
      int u = get<1>(g[i]), v = get<2>(g[i]), w = get<0>(g[i]);
      if (not is_same_set(u, v)) {
        union_set(u, v);
        dag[u].emplace_back(v, w);
        dag[v].emplace_back(u, w);
      }
    }

    max_passengers = (1 << 28);
    visited.assign(n, false);
    dfs(s);
    --max_passengers;

    cout << "Scenario #" << ++scenario << endl;
    cout << "Minimum Number of Trips = "
         << t / max_passengers + (t % max_passengers ? 1 : 0) << endl
         << endl;
  }
}