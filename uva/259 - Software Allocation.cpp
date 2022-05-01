#include <algorithm>
#include <ciso646>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/* Bipartite matching, resolvido via max flow */

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
  string buf;
  ios_base::sync_with_stdio(false);
  while (getline(cin, buf)) {
    edge.clear();
    g.clear();
    g.resize(40);
    s = 38, t = 39, n = 40;

    for (int i = 0; i < 10; ++i)
      add_edge(i, t, 1);

    int expected_flow = 0;
    do {
      int program = buf[0] - 'A' + 10;
      int f = buf[1] - '0';
      expected_flow += f;
      add_edge(s, program, f);
      for (int i = 3; buf[i] != ';'; ++i)
        add_edge(program, buf[i] - '0', 1);
    } while (getline(cin, buf) and buf.size());

    if (push_relabel_max_flow() != expected_flow) {
      cout << "!\n";
    } else {
      for (int v = 0; v < 10; ++v) {
        bool has_mate = false;
        for (int e : g[v]) {
          if (edge[e].to != t and edge[e].flow == -1) {
            cout << (char)(edge[e].to - 10 + 'A');
            has_mate = true;
            break;
          }
        }
        if (not has_mate)
          cout << '_';
      }
      cout << endl;
    }
  }
}