#include <algorithm>
#include <ciso646>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define MAX_V 100000

using namespace std;
using ii = pair<int, int>;

/* Não faz sentido nenhum. Acho que este problema está broken no UVa. */

int cost[15], dist[MAX_V], n, k;
vector<vector<ii>> g;
string buf;

void dijkstra() {
  memset(dist, -1, sizeof dist);
  priority_queue<ii, vector<ii>, greater<ii>> pq;

  for (int i = 0; i < n; ++i)
    if (g[i * 100].size()) {
      pq.emplace(0, i * 100);
      dist[i * 100] = 0;
    }

  while (pq.size()) {
    int w = pq.top().first, v = pq.top().second;
    pq.pop();
    if (dist[v] != w)
      continue;
    for (auto &e : g[v]) {
      int d = e.second + w;
      if (dist[e.first] == -1 or dist[e.first] > d) {
        dist[e.first] = d;
        pq.emplace(d, e.first);
      }
    }
  }
}

int main() {
  while (cin >> n >> k) {
    if (k == 0) {
      cout << 0 << endl;
      continue;
    }

    g.clear();
    g.resize(MAX_V);
    for (int i = 0; i < n; ++i)
      cin >> cost[i];

    getline(cin, buf);
    for (int i = 0; i < n; ++i) {
      getline(cin, buf);
      istringstream ss(buf);

      vector<int> floors;
      for (int x; ss >> x;)
        floors.push_back(x);
      sort(begin(floors), end(floors));

      for (int j = 1; j < floors.size(); ++j) {
        int v = floors[j] + i * 100, u = floors[j - 1] + i * 100;
        int d = abs(v - u) * cost[i];
        g[v].emplace_back(u, d);
        g[u].emplace_back(v, d);
      }

      for (auto f : floors) {
        for (int j = i - 1; j >= 0; --j) {
          int u = f + j * 100, v = f + i * 100;
          if (g[u].size()) {
            g[u].emplace_back(v, 60);
            g[v].emplace_back(u, 60);
          }
        }
      }
    }

    dijkstra();
    int min_dist = (1 << 30);
    for (int i = 0; i < n; ++i) {
      int v = k + i * 100;
      if (dist[v] != -1)
        min_dist = min(min_dist, dist[v]);
    }

    if (min_dist == (1 << 30))
      cout << "IMPOSSIBLE" << endl;
    else
      cout << min_dist << endl;
  }
}