#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using ll = long long;
using namespace std;

struct MCMF {
  struct Edge {
    ll from, to;
    ll cap, flow, wt;
    Edge(ll from, ll to, ll cap, ll flow, ll wt)
        : from(from), to(to), cap(cap), flow(flow), wt(wt) {}
  };
  vector<Edge> edge;
  vector<ll> pred, in_queue;
  vector<ll> dist;
  vector<vector<ll>> g;
  ll n, s, t;
  MCMF(ll n, ll s, ll t) : n(n), s(s), t(t) { g.resize(n + 10); }

  void add_edge(ll u /* from */, ll v /* to */, ll w /* cost */,
                ll c /* capacity */) {
    g[u].push_back(edge.size());
    edge.push_back(Edge(u, v, c, 0, w));
    g[v].push_back(edge.size());
    edge.push_back(Edge(v, u, 0, 0, -w));
  }
  bool spfa() {
    dist.assign(n, numeric_limits<ll>::max());
    pred.assign(n, -1);
    in_queue.assign(n, false);
    queue<ll> q;
    q.push(s);
    dist[s] = 0, in_queue[s] = true;
    while (q.size()) {
      ll v = q.front();
      q.pop();
      in_queue[v] = false;
      for (ll i = 0; i < g[v].size(); ++i) {
        ll e = g[v][i];
        if (edge[e].cap - edge[e].flow <= 0)
          continue;
        ll u = edge[e].to;
        ll d = dist[v] + edge[e].wt;
        if (dist[u] > d) {
          dist[u] = d;
          pred[u] = e;
          if (not in_queue[u]) {
            in_queue[u] = true;
            q.push(u);
          }
        }
      }
    }
    return dist[t] != numeric_limits<ll>::max();
  }
  pair<ll, ll> min_cost_max_flow() {
    ll total_flow = 0, total_cost = 0;
    while (spfa()) {
      ll f = numeric_limits<ll>::max();
      for (ll e = pred[t]; e != -1; e = pred[edge[e].from]) {
        f = min(f, edge[e].cap - edge[e].flow);
      }
      if (f == 0)
        continue;
      for (ll e = pred[t]; e != -1; e = pred[edge[e].from]) {
        edge[e].flow += f;
        edge[e ^ 1].flow -= f;
      }
      total_flow += f;
      total_cost += (f * dist[t]);
    }
    return {total_flow, total_cost};
  }
};

int main() {
  int n, m, inst = 0;
  while (cin >> n >> m) {
    MCMF mcmf(n + 1, n, n - 1);
    vector<vector<ll>> es;
    for (int i = 0; i < m; ++i) {
      vector<ll> e(3);
      cin >> e[0] >> e[1] >> e[2];
      --e[0], --e[1];
      es.push_back(e);
    }
    int d, k;
    cin >> d >> k;
    for (int i = 0; i < m; ++i) {
      mcmf.add_edge(es[i][0], es[i][1], es[i][2], k);
      mcmf.add_edge(es[i][1], es[i][0], es[i][2], k);
    }
    mcmf.add_edge(n, 0, 0, d);
    mcmf.add_edge(0, n, 0, d);
    pair<ll, ll> ans = mcmf.min_cost_max_flow();
    cout << "Instancia " << ++inst << endl;
    if (ans.first < d)
      cout << "impossivel" << endl;
    else
      cout << ans.second << endl;
    cout << endl;
  }
}