#include <iostream>
#include <vector>

using namespace std;

/* I confess that if I didn't have the tip to check for bipartite graphs, I
 * wouldn't have thought of it.
 *
 * Every middle vertex in the claws is connected to only the paws' vertices,
 * and the paws' vertices are connected to only middle vertices. Just check
 * if the graph is bipratite. */

int V;
vector<vector<int>> g;

bool bipartite() {
  vector<int> color(400, -1), q(1, 1);
  color[1] = 0;
  while (q.size()) {
    int v = q.back();
    q.pop_back();
    for (int i = 0; i < g[v].size(); ++i) {
      if (color[g[v][i]] == color[v])
        return false;
      else if (color[g[v][i]] == -1) {
        color[g[v][i]] = 1 - color[v];
        q.push_back(g[v][i]);
      }
    }
  }
  return true;
}

int main() {
  while (cin >> V, V != 0) {
    g.clear();
    g.resize(400);
    int u, v;
    while (cin >> u >> v, u != 0) {
      g[u].push_back(v);
      g[v].push_back(u);
    }
    cout << (bipartite() ? "YES" : "NO") << endl;
  }
}