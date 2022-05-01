#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/*
* you can view the sticks and their relations as a graph: there is an edge from
* a to b if stick b is on top of a (b depends on a).
*
* to take all the sticks equals doing a flood fill on the graph. however, we
* must detect cycles during our flood fill; for that, not only do we maintain
* a vector of bool 'visited', we also have one 'taken'. a node is marked as
* visited when it has been seen by the flood fill, but the other nodes that
* are on top of it have not been removed yet. a node is taken when the stick
* has been removed.
*
* if we visit a node that has already been taken, ok, do nothing.
* if we visit a node that has already been visited, it means that one of the
* sticks that are on top of it is also on the bottom of it, which constitute an
* impossible situation.
**/

vector<vector<int>> g;
vector<bool> visited, taken;
vector<int> order;
bool possible;

void flood_fill(int v) {
  if (taken[v] or not possible)
    return;
  if (visited[v]) {
    possible = false;
    return;
  }
  visited[v] = true;
  for (auto u : g[v])
    flood_fill(u);
  order.push_back(v);
  taken[v] = true;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 and m == 0)
      break;
    g.clear();
    g.resize(n);
    visited.assign(n, false);
    taken.assign(n, false);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      --x, --y;
      g[y].push_back(x);
    }
    order.clear();
    possible = true;
    for (int i = 0; i < n; ++i)
      flood_fill(i);
    if (not possible)
      cout << "IMPOSSIBLE" << endl;
    else {
      for (auto i : order)
        cout << i + 1 << endl;
    }
  }
}