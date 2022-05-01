#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* Para garantir que nenhum vértice seja usado mais de uma vez, separa
* um vértice v em dois: v1 (de entrada, tal que todo (u, v) em E
* então (u, v1) em E') e v2 (de saída, tal que todo (v, u) em E então
* (v2, u) em E'). Cria a aresta direcionada (v1, v2) com capacidade 1.
* Todos os bancos são conectados a s, e todas as bordas são conectadas as t.
* */

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

int b, nr, nc;
int dc[] = {-1, 1, 0, 0}, dr[] = {0, 0, -1, 1};

bool inside_bounds(int r, int c) {
  return r >= 0 and c >= 0 and r < nr and c < nc;
}

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    cin >> nr >> nc >> b;
    n = nr * nc;
    edge.clear();
    g.clear();
    g.resize(2 * n + 2);
    s = 2 * n;
    t = 1 + s;
    for (int r = 0; r < nr; ++r) {
      for (int c = 0; c < nc; ++c) {
        int irc = c + r * nc;
        add_edge(irc, irc + n, 1);
        for (int i = 0; i < 4; ++i) {
          int ri = r + dr[i], ci = c + dc[i];
          if (not inside_bounds(ri, ci)) {
            add_edge(irc + n, t, 1);
          } else {
            add_edge(n + ci + ri * nc, irc, 1);
          }
        }
      }
    }

    for (int i = 0; i < b; ++i) {
      int r, c;
      cin >> r >> c;
      --r, --c;
      int irc = c + r * nc;
      add_edge(s, irc, 1);
    }

    n = t + 1;
    if (push_relabel_max_flow() < b)
      cout << "not possible" << endl;
    else
      cout << "possible" << endl;
  }
}