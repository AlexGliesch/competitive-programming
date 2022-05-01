#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

/*
 * this is essentially checking if the graph is bipartite. we can solve this
 * with a dfs.
 *
 * for each node, store the color of it (0: black, 1: white, -1: not visited).
 * when visiting a node in the dfs, if any neighbour has the same color of the
 * current node, the graph cannot be bipartite. otherwise, set the color of
 * each neighbour to 1 - the color of current node, and visit it recursively.  *
 * */

int n, color[210];
vector<vector<int>> g;

bool dfs(int v) {
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (color[u] == color[v])
      return false;
    else if (color[u] == -1) {
      color[u] = 1 - color[v];
      if (!dfs(u))
        return false;
    }
  }
  return true;
}

int main() {
  while (cin >> n, n != 0) {
    int l;
    cin >> l;
    g.clear();
    g.resize(n);
    for (int i = 0; i < l; ++i) {
      int x, y;
      cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    memset(color, -1, sizeof color);
    color[0] = 0;

    cout << (dfs(0) ? "BICOLORABLE." : "NOT BICOLORABLE.") << endl;
  }
}