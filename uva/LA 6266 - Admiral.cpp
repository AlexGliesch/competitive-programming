#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define INF (1 << 28)
#define enter(v) ((v) + n)
#define leave(v) (v)

using namespace std;

struct Edge {
  Edge(int u, int v, int c, int w, int f)
      : from(u), to(v), cap(c), wt(w), flow(f) {}
  int from, to, cap, wt, flow;
};
vector<Edge> edge;
vector<int> pred, dist, in_queue;
int n, m, s, t;
vector<vector<int>> g;

void add_edge(int u, int v, int w, int c) {
  g[u].push_back(edge.size());
  edge.push_back(Edge(u, v, c, w, 0));
  g[v].push_back(edge.size());
  edge.push_back(Edge(v, u, 0, -w, 0));
}

bool dijkstra() {
  dist.assign(n, -1);
  pred.assign(n, -1);
  priority_queue<pair<int, int>> pq;
  dist[s] = 0;
  pq.push(make_pair(0, s));
  while (pq.size()) {
    int v = pq.top().second, w = -pq.top().first;
    pq.pop();
    if (dist[v] != w)
      continue;
    if (v == t)
      break;
    for (int i = 0; i < g[v].size(); ++i) {
      int e = g[v][i];
      int u = edge[e].to, d = edge[e].wt + w;
      ;
      if (edge[e].cap - edge[e].flow <= 0)
        continue;
      if (dist[u] == -1 or dist[u] > d) {
        pred[u] = e;
        dist[u] = d;
        pq.push(make_pair(-d, u));
      }
    }
  }
  return pred[t] != -1;
}

int min_cost_max_flow() {
  int total_flow = 0, total_cost = 0;
  while (dijkstra()) {
    int f = INF;
    for (int e = pred[t]; e != -1; e = pred[edge[e].from])
      f = min(f, edge[e].cap - edge[e].flow);
    if (f == 0)
      continue;
    for (int e = pred[t]; e != -1; e = pred[edge[e].from]) {
      edge[e].flow += f;
      edge[e ^ 1].flow -= f;
    }
    total_flow += f;
    total_cost += (int)(f * dist[t]);
  }
  return total_cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> n >> m) {
    edge.clear();
    g.clear();
    g.resize(n * 2);
    for (int i = 0; i < m; ++i) {
      int a, b, c;
      cin >> a >> b >> c;
      --a, --b;
      add_edge(leave(a), enter(b), c, 1);
    }
    add_edge(enter(0), leave(0), 0, 2);
    add_edge(enter(n - 1), leave(n - 1), 0, 2);
    for (int v = 1; v < n - 1; ++v)
      add_edge(enter(v), leave(v), 0, 1);

    s = enter(0), t = leave(n - 1);
    n += n;
    cout << min_cost_max_flow() << endl;
  }
}