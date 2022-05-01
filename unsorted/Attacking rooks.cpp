#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;

struct PushRelabelMaxFlow {
  struct Edge {
    Edge(int from, int to, int cap, int flow)
        : from(from), to(to), cap(cap), flow(flow) {}

    int from, to, cap, flow;
  };

  vector<Edge> edge;
  vector<vi> g;

  int n, s, t;
  vector<int> excess, dist, active, ct;
  queue<int> q;

  PushRelabelMaxFlow(int n, int s, int t) : n(n), s(s), t(t) { g.resize(n); }

  void add_edge(int u, int v, int c) {
    g[u].push_back(edge.size());
    edge.push_back(Edge(u, v, c, 0));
    g[v].push_back(edge.size());
    edge.push_back(Edge(v, u, 0, 0));
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
    for (int i = 0; i < g[v].size(); ++i) {
      int e = g[v][i];
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

    for (int i = 0; i < g[s].size(); ++i) {
      int e = g[s][i];
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
    for (int i = 0; i < g[s].size(); ++i) {
      int e = g[s][i];
      flow += edge[e].flow;
    }

    return flow;
  }
};

int main() {
  int n;
  while (cin >> n) {
    vector<vc> mat(n, vector<char>(n, ' '));

    // Lê a matriz do tabuleiro
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        cin >> mat[i][j];
      }

    // Divide os segmentos continuos de linhas
    int p = 1;
    vector<vi> mat_lin(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++, p++)
      for (int j = 0; j < n; j++) {
        mat_lin[i][j] = (mat[i][j] == '.') ? p : -1;
        if (mat[i][j] == 'X')
          p++;
      }
    int c_lin = p - 1;

    // Divide os segmentos continuos de colunas
    vector<vi> mat_col(n, vector<int>(n, 0));
    for (int j = 0; j < n; j++, p++)
      for (int i = 0; i < n; i++) {
        mat_col[i][j] = (mat[i][j] == '.') ? p : -1;
        if (mat[i][j] == 'X')
          p++;
      }
    p--;

    // Cria o grafo de emparelhamento bipartido entre os segmentos.
    PushRelabelMaxFlow mf(p + 2, 0, p + 1);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (mat_lin[i][j] != -1) {
          mf.add_edge(mat_lin[i][j], mat_col[i][j], 1);
        }

    for (int i = 1; i <= c_lin; i++) {
      mf.add_edge(0, i, 1);
    }

    for (int i = c_lin + 1; i <= p; i++) {
      mf.add_edge(i, p + 1, 1);
    }

    // Calcula o max flow
    cout << mf.push_relabel_max_flow() << endl;
  }

  return 0;
}