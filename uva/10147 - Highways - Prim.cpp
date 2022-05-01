#include <algorithm>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* Partial MST, significa que algumas arestas já existem e devem ser usadas
 * para a MST. Para resolver isto com prim, basta colocar o peso destas arestas
 * como 0, dessa maneira o algoritmo vai selecionar elas primeiro.*/

typedef pair<int, int> ii;

int n, m, pt[750][2], g[750][750];
bool taken[750];

int prim() {
  memset(taken, false, n);
  priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<pair<int, ii>>>
      pq;

  taken[0] = true;
  for (int v = 1; v < n; ++v)
    pq.push(make_pair(g[0][v], ii(0, v)));
  int cost = 0;

  while (pq.size()) {
    int w = pq.top().first, p = pq.top().second.first,
        u = pq.top().second.second;
    pq.pop();
    if (taken[u])
      continue;
    if (g[u][p] != 0)
      cout << u + 1 << ' ' << p + 1 << endl;
    cost += w;
    taken[u] = true;
    for (int v = 0; v < n; ++v) {
      if (!taken[v])
        pq.push(make_pair(g[u][v], ii(u, v)));
    }
  }
  return cost;
}

int main() {
  int t;
  cin >> t;
  for (int b = 0; b < t; ++b) {
    if (b > 0)
      cout << endl;
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> pt[i][0] >> pt[i][1];

    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        g[i][j] = g[j][i] =
            pow(pt[i][0] - pt[j][0], 2) + pow(pt[i][1] - pt[j][1], 2);

    cin >> m;
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      --x, --y;
      g[x][y] = g[y][x] = 0;
    }

    if (prim() == 0)
      cout << "No new highways need" << endl;
  }
}