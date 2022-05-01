#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* Start a dfs from each node. At each intersection in the road, split the
 * recursion in two. Since m <= 25, an integer can be used as 'visited'
 * list. Also, mind that the visited list stores the edges visited, not the
 * nodes (since a node can be visted more than once). */

int m, n, longest;
vector<vector<pair<int, int>>> g;

void dfs(int size, int visited, int v) {
  longest = max(longest, size);
  for (const auto &p : g[v]) {
    if (not(visited & (1 << p.second)))
      dfs(1 + size, visited | (1 << p.second), p.first);
  }
}

int main() {
  while (cin >> n >> m, m and n) {
    g.clear();
    g.resize(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      g[u].emplace_back(v, i);
      g[v].emplace_back(u, i);
    }
    longest = 0;
    for (int v = 0; v < n; ++v)
      dfs(0, 0, v);
    cout << longest << endl;
  }
}