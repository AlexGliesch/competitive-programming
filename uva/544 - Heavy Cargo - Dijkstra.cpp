#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

int n, m, s, t, dist[210];
vector<vector<ii>> g;

void bfs() {
  priority_queue<ii> pq;
  memset(dist, -1, sizeof(int) * n);
  dist[s] = (1 << 28);
  pq.push(make_pair((1 << 28), s));

  while (pq.size()) {
    int cost = pq.top().first, u = pq.top().second;
    pq.pop();
    if (u == t)
      break;
    if (dist[u] != cost)
      continue;

    for (int i = 0; i < g[u].size(); ++i) {
      int v = g[u][i].second, w = min(g[u][i].first, cost);
      if (dist[v] < w) {
        dist[v] = w;
        pq.push(make_pair(w, v));
      }
    }
  }
}

int main() {
  int scenario_counter = 1;
  while (cin >> n >> m, n != 0 && m != 0) {
    g.clear();
    g.resize(n);

    map<string, int> index;
    int index_counter = 0;
    for (int i = 0; i < m; ++i) {
      string s, t;
      cin >> s >> t;
      int w;
      cin >> w;
      if (index.count(s) == 0)
        index[s] = index_counter++;
      if (index.count(t) == 0)
        index[t] = index_counter++;
      g[index[s]].push_back(make_pair(w, index[t]));
      g[index[t]].push_back(make_pair(w, index[s]));
    }

    string ss, st;
    cin >> ss >> st;
    s = index[ss], t = index[st];

    bfs();
    cout << "Scenario #" << scenario_counter++ << endl;
    cout << dist[t] << " tons" << endl << endl;
  }
}