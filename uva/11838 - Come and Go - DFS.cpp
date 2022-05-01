#include <iostream>
#include <vector>

using namespace std;

/* Initially, I solved it by using N dfs's: just check if it's possible to
 * reach every node starting from every node. I thought I would get TLE
 * but it worked fine.
 *
 * But, as the problem link said "Finding Strongly Connected Components", I
 * decided to solve it also through SCC (just check if there only exists 1),
 * since I didn't really know this kind of problem and wanted to try the
 * algorithms. I solve it with both Tarjan's and Kosajaru's; personally, I
 * found Kosajaru's much simpler, even though Tarjan's has a slightly better
 * runtime.
 * */

int V, E;
vector<vector<int>> g;
vector<bool> visited;
int num_visited;

void dfs(int v) {
  if (visited[v])
    return;
  visited[v] = true, ++num_visited;
  for (int i = 0; i < g[v].size(); ++i)
    dfs(g[v][i]);
}

int main() {
  while (cin >> V >> E, V != 0) {
    g.clear();
    g.resize(V + 1);
    for (int i = 0; i < E; ++i) {
      int u, v, p;
      cin >> u >> v >> p;
      g[u].push_back(v);
      if (p == 2)
        g[v].push_back(u);
    }

    bool ok = true;
    for (int v = 1; v <= V; ++v) {
      visited.assign(V + 1, false);
      num_visited = 0;
      dfs(v);
      if (num_visited != V) {
        ok = false;
        break;
      }
    }

    cout << (ok ? 1 : 0) << endl;
  }
}