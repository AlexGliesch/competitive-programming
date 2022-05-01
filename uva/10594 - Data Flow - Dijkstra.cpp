#include <queue>
#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Edge {
  ll from, to, cap, flow, wt;
};
vector<Edge> edge;
vector<ll> pred, dist, in_queue;
ll n, m, s, t, d, k;
vector<vector<ll>> g;

void add_edge(ll u, ll v, ll w, ll c) {
  g[u].push_back(edge.size());
  edge.push_back({u, v, c, 0, w});
  g[v].push_back(edge.size());
  edge.push_back({v, u, 0, 0, -w});
}

bool dijkstra() {
  dist.assign(n, -1);
  pred.assign(n, -1);
  priority_queue<pair<ll, ll>> pq;
  dist[s] = 0;
  pq.emplace(0, s);
  while (pq.size()) {
    ll v = pq.top().second, w = -pq.top().first;
    pq.pop();
    if (dist[v] != w)
      continue;
    if (v == t)
      break;
    for (ll e : g[v]) {
      ll u = edge[e].to, d = edge[e].wt + w;
      ;
      if (edge[e].cap - edge[e].flow <= 0)
        continue;
      if (dist[u] == -1 or dist[u] > d) {
        pred[u] = e;
        dist[u] = d;
        pq.emplace(-d, u);
      }
    }
  }
  return pred[t] != -1;
}

ll min_cost_max_flow() {
  ll total_flow = 0, total_cost = 0;
  while (dijkstra()) {
    ll f = numeric_limits<ll>::max();
    for (ll e = pred[t]; e != -1; e = pred[edge[e].from])
      f = min(f, edge[e].cap - edge[e].flow);
    if (f == 0)
      continue;
    for (ll e = pred[t]; e != -1; e = pred[edge[e].from]) {
      edge[e].flow += f;
      edge[e ^ 1].flow -= f;
    }
    total_flow += f;
    total_cost += (ll)(f * dist[t]);
  }
  return (total_flow < d) ? -1 : total_cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> n >> m) {
    edge.clear();
    g.clear();
    g.resize(++n + 10);
    vector<int> u, v, w;
    for (ll i = 0; i < m; ++i) {
      ll ui, vi, wi;
      cin >> ui >> vi >> wi;
      u.push_back(ui), v.push_back(vi), w.push_back(wi);
    }
    cin >> d >> k;
    for (ll i = 0; i < m; ++i) {
      add_edge(u[i], v[i], w[i], k);
      add_edge(v[i], u[i], w[i], k);
    }
    add_edge(0, 1, 0, d);
    s = 0, t = n - 1;
    ll f = min_cost_max_flow();
    if (f == -1)
      cout << "Impossible." << endl;
    else
      cout << f << endl;
  }
}