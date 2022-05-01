#include <algorithm>
#include <ciso646>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* Basta fazer o max flow. */

struct Edge {
  int from, to, cap, flow;
};
vector<Edge> edge;
vector<vector<int>> g;
int n, s, t;
vector<int> excess, dist, active, ct;
queue<int> q;

void add_edge(int u, int v, int c) {
  g[u].push_back(edge.size());
  edge.push_back({u, v, c, 0});
  g[v].push_back(edge.size());
  edge.push_back({v, u, 0, 0});
}

void enqueue(int v) {
  if (not active[v] and excess[v] > 0) {
    active[v] = true;
    q.push(v);
  }
}

void push(int e) {
  int amt = min(excess[edge[e].from], edge[e].cap - edge[e].flow);
  if (dist[edge[e].from] <= dist[edge[e].to] or amt == 0)
    return;
  edge[e].flow += amt;
  edge[e ^ 1].flow -= amt;
  excess[edge[e].to] += amt;
  excess[edge[e].from] -= amt;
  enqueue(edge[e].to);
}

void gap(int k) {
  for (int v = 0; v < n; ++v) {
    if (dist[v] < k)
      continue;
    --ct[dist[v]];
    dist[v] = max(dist[v], n + 1);
    ++ct[dist[v]];
    enqueue(v);
  }
}

void relabel(int v) {
  --ct[dist[v]];
  dist[v] = 2 * n;
  for (int e : g[v]) {
    if (edge[e].cap - edge[e].flow > 0)
      dist[v] = min(dist[v], dist[edge[e].to] + 1);
  }
  ++ct[dist[v]];
  enqueue(v);
}

void discharge(int v) {
  for (int i = 0; excess[v] > 0 and i < g[v].size(); ++i)
    push(g[v][i]);
  if (excess[v] > 0) {
    if (ct[dist[v]] == 1)
      gap(dist[v]);
    else
      relabel(v);
  }
}

int push_relabel_max_flow() {
  excess.assign(n, 0);
  dist.assign(n, 0);
  active.assign(n, 0);
  ct.assign(2 * n, 0);

  ct[0] = n - 1;
  ct[n] = 1;
  dist[s] = n;
  active[s] = active[t] = true;

  for (auto &e : g[s]) {
    excess[s] += edge[e].cap;
    push(e);
  }

  while (q.size()) {
    int v = q.front();
    q.pop();
    active[v] = false;
    discharge(v);
  }

  int flow = 0;
  for (auto &e : g[s])
    flow += edge[e].flow;
  return flow;
}

int main() {
  ios_base::sync_with_stdio(false);
  int num_case = 1, c;
  while (cin >> n, n) {
    cin >> s >> t >> c;
    --s, --t;
    edge.clear();
    g.clear();
    g.resize(n);
    for (int i = 0; i < c; ++i) {
      int u, v, c;
      cin >> u >> v >> c;
      --u, --v;
      add_edge(u, v, c);
      add_edge(v, u, c);
    }
    cout << "Network " << num_case++ << endl;
    cout << "The bandwidth is " << push_relabel_max_flow() << ".\n\n";
  }
}