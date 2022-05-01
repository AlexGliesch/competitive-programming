#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

int n, m, total_cost;
vector<vector<ii>> g;
vector<bool> taken;

int prim() {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  taken[0] = true;
  int cost = 0;

  for (int i = 0; i < g[0].size(); ++i)
    pq.push(g[0][i]);

  while (pq.size()) {
    int w = pq.top().first, u = pq.top().second;
    pq.pop();
    if (taken[u])
      continue;
    taken[u] = true;
    cost += w;
    for (int i = 0; i < g[u].size(); ++i) {
      if (!taken[g[u][i].second])
        pq.push(g[u][i]);
    }
  }
  return cost;
}

int main() {
  while (cin >> n >> m, n != 0 && m != 0) {
    g.clear();
    g.resize(n);
    taken.assign(n, false);
    total_cost = 0;
    for (int i = 0; i < m; ++i) {
      int x, y, z;
      cin >> x >> y >> z;
      total_cost += z;
      g[x].push_back(make_pair(z, y));
      g[y].push_back(make_pair(z, x));
    }

    cout << total_cost - prim() << endl;
  }
}