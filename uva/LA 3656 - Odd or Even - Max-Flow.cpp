#include <algorithm>
#include <ciso646>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
  int from, to, cap, flow;
};
vector<Edge> edge;
vector<int> pred;
int n, s, t;
vector<vector<int>> g;

void add_edge(int u, int v, int c) {
  g[u].push_back(edge.size());
  edge.push_back(Edge(u, v, c, 0));
  g[v].push_back(edge.size());
  edge.push_back(Edge(v, u, 0, 0));
}

bool bfs() {
  pred.assign(n, -1);
  queue<int> q;
  q.push(s);
  pred[s] = -2; /* some unique value */
  while (q.size()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < g[v].size(); ++i) {
      int e = g[v][i];
      if (edge[e].cap - edge[e].flow <= 0)
        continue;
      int u = edge[e].to;
      if (pred[u] == -1) {
        pred[u] = e;
        q.push(u);
      }
    }
  }
  return pred[t] != -1;
}

int edmonds_karp_max_flow() {
  int total_flow = 0;
  while (bfs()) {
    int f = INT_MAX;
    for (int e = pred[t]; e != pred[s]; e = pred[edge[e].from])
      f = min(f, edge[e].cap - edge[e].flow);
    if (f == 0)
      continue;
    for (int e = pred[t]; e != pred[s]; e = pred[edge[e].from]) {
      edge[e].flow += f;
      edge[e ^ 1].flow -= f;
    }
    total_flow += f;
  }
  return total_flow;
}

int main() {
  while (cin >> n, n) {
    int old_n = n;
    vector<int> v1(n + 1), v2(n + 1);
    for (int i = 1; i <= n; ++i)
      cin >> v1[i];
    for (int i = 1; i <= n; ++i)
      cin >> v2[i];
    edge.clear();
    g.clear();
    g.resize(2 * (n + 1) + 2);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if ((v1[i] + v2[j]) % 2 != 0) {
          add_edge(i, j + n, 1);
        }
      }
      /* Edges from s to every vertex in U */
      add_edge(2 * n + 1, i, 1);

      /* Edges from every vertex in U to t*/
      add_edge(i + n, 2 * n + 2, 1);
    }
    s = 2 * n + 1, t = 2 * n + 2, n = t + 1;
    cout << old_n - edmonds_karp_max_flow() << endl;
  }
}