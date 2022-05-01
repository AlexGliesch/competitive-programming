#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int from, to, cap, flow, wt;
};
vector<Edge> edge;
vector<int> pred, dist, in_queue;
int n, m, s, t;
vector<vector<int>> g;

void add_edge(int u, int v, int w, int c) {
  g[u].push_back(edge.size());
  edge.push_back({u, v, c, 0, w});
  g[v].push_back(edge.size());
  edge.push_back({v, u, 0, 0, -w});
}

bool spfa() {
  dist.assign(n, -1);
  pred.assign(n, -1);
  in_queue.assign(n, false);
  queue<int> q;
  q.push(s);
  dist[s] = 0, in_queue[s] = true;
  while (q.size()) {
    int v = q.front();
    in_queue[v] = false;
    q.pop();
    for (auto e : g[v]) {
      if (edge[e].cap - edge[e].flow <= 0)
        continue;
      int u = edge[e].to, d = dist[v] + edge[e].wt;
      if (dist[u] == -1 or dist[u] > d) {
        dist[u] = d;
        pred[u] = e;
        if (not in_queue[u]) {
          in_queue[u] = true;
          q.push(u);
        }
      }
    }
  }
  return dist[t] != -1;
}

int min_cost_max_flow() {
  int total_flow = 0, total_cost = 0;
  while (spfa()) {
    int f = numeric_limits<int>::max();
    for (int e = pred[t]; e != -1; e = pred[edge[e].from])
      f = min(f, edge[e].cap - edge[e].flow);
    if (f == 0)
      continue;
    for (int e = pred[t]; e != -1; e = pred[edge[e].from]) {
      edge[e].flow += f;
      edge[e ^ 1].flow -= f;
    }
    total_flow += f;
    total_cost += f * dist[t];
  }
  return (total_flow < 2) ? -1 : total_cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> n, n) {
    edge.clear();
    g.clear();
    g.resize(++n + 10);
    cin >> m;
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      add_edge(u, v, w, 1);
      add_edge(v, u, w, 1);
    }
    add_edge(0, 1, 0, 2);
    s = 0, t = n - 1;
    int f = min_cost_max_flow();
    if (f == -1)
      cout << "Back to jail" << endl;
    else
      cout << f << endl;
  }
}