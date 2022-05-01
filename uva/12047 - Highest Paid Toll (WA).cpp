#include <algorithm>
#include <ciso646>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#define INF (1 << 30)

using namespace std;

/* I got the idea from the internet. For each edge that goes from u to v
 * with weight w, if there exists a path with cost less than p passing through
 * that edge, then its cost is dist(s, u) + w + dist(v, t) <= p. So we run
 * dijkstra to find all distances to s and to t (using the reverse graph),
 * and iterate through all edges to see which ones satisfy that condition. The
 * one with the greatest weight w is the solution.
 * Seems to make a lot of sense, but I'm getting WA somehow. */

using ii = pair<int, int>;

vector<vector<ii>> g, gt;
vector<int> dist_s, dist_t;
vector<tuple<int, int, int>> edges;
priority_queue<ii, vector<ii>, greater<ii>> pq;
int n, m, s, t, p;

void dijkstra(vector<vector<ii>> &g, vector<int> &dist, int s) {
  dist.assign(n, INF);
  pq.emplace(0, s);
  dist[s] = 0;
  while (pq.size()) {
    int w = pq.top().first, u = pq.top().second;
    pq.pop();
    if (dist[u] != w)
      continue;
    for (const auto &e : g[u]) {
      int v = e.first, d = e.second + w;
      if (dist[v] > d)
        pq.emplace(dist[v] = d, v);
    }
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> s >> t >> p;
    --s, --t;
    g.clear();
    g.resize(n);
    gt.clear();
    gt.resize(n);
    edges.clear();
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      cin >> u >> v >> c;
      --u, --v;
      g[u].emplace_back(v, c);
      gt[v].emplace_back(u, c);
      edges.emplace_back(c, u, v);
    }
    sort(begin(edges), end(edges));
    dijkstra(g, dist_s, s);
    dijkstra(gt, dist_t, t);
    int ans = -1;
    for (int e = m - 1; e >= 0; --e) {
      int u = get<1>(edges[e]), v = get<2>(edges[e]), w = get<0>(edges[e]);
      if (dist_s[u] + w + dist_t[v] <= p) {
        ans = w;
        break;
      }
    }
    cout << ans << endl;
  }
}