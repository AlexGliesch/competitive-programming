#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

/* Basta fazer o max flow. */

struct EdmondsKarpMaxFlow {
  struct Edge {
    Edge(int from, int to, int cap, int flow)
        : from(from), to(to), cap(cap), flow(flow) {}
    int from, to, cap, flow;
  };

  vector<Edge> edge;
  vector<int> pred;
  int n, s, t;
  vector<vector<int>> g;

  EdmondsKarpMaxFlow(int n, int s, int t) : n(n), s(s), t(t) { g.resize(n); }

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
      int f = numeric_limits<int>::max();
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
};

int main() {
  ios_base::sync_with_stdio(false);
  int num_case = 1, c;
  int n, s, t;
  while (cin >> n, n) {
    cin >> s >> t >> c;
    --s, --t;
    EdmondsKarpMaxFlow ek(n, s, t);
    for (int i = 0; i < c; ++i) {
      int u, v, cap;
      cin >> u >> v >> cap;
      --u, --v;
      ek.add_edge(u, v, cap);
      ek.add_edge(v, u, cap);
    }
    cout << "Network " << num_case++ << endl;
    cout << "The bandwidth is " << ek.edmonds_karp_max_flow() << ".\n\n";
  }
}