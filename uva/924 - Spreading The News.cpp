#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* BFS. The boom day is the distance from source. The boom size is the number
 * of nodes that you add in the queue for each distance.
 *
 * Another possible implementation is store a vector mapping the boom day
 * to the boom size. */

int V, max_boom, max_boom_day;
vector<vector<int>> g;

void bfs(int s) {
  queue<int> q;
  q.push(s);
  vector<int> dist(V, -1);
  dist[s] = 0;
  int cur_dist = 0;
  max_boom = 1, max_boom_day = 1;

  while (q.size()) {
    int v = q.front();
    q.pop();
    if (dist[v] != cur_dist) {
      if (q.size() + 1 > max_boom) {
        max_boom = q.size() + 1;
        max_boom_day = dist[v];
      }
      cur_dist = dist[v];
    }
    for (int i = 0; i < g[v].size(); ++i) {
      if (dist[g[v][i]] == -1) {
        dist[g[v][i]] = 1 + dist[v];
        q.push(g[v][i]);
      }
    }
  }
}

int main() {
  cin >> V;
  g.resize(V);
  for (int v = 0; v < V; ++v) {
    int x;
    cin >> x;
    g[v].resize(x);
    for (int u = 0; u < x; ++u)
      cin >> g[v][u];
  }

  int t;
  cin >> t;
  while (t--) {
    int s;
    cin >> s;
    if (g[s].empty())
      cout << 0 << endl;
    else {
      bfs(s);
      cout << max_boom << ' ' << max_boom_day << endl;
    }
  }
}