#include <algorithm>
#include <ciso646>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#define INF (1 << 30)

using namespace std;

/* Dijkstra + DP. Pra ser bem sincero, não entendi muito bem a DP: peguei
 * de um site. Guarda para cada vértice e cada quantidade possível
 * de fuel nele o valor do custo mínimo até ele.
 * Detalhe: tem que testar adicionando fuel de 1 em 1, e não sempre enxendo
 * o tanque. */

using ii = pair<int, int>;
using iii = tuple<int, int, int>;

vector<vector<ii>> g;
vector<int> price;
vector<vector<int>> dp;
int n, m, s, t, cap;

void dijkstra() {
  /*tuple 0: cost, 1: fuel, 2: node */
  priority_queue<iii, vector<iii>, greater<iii>> pq;
  dp.assign(n, vector<int>(cap + 1, INF));
  dp[s][0] = 0;
  pq.emplace(0, 0, s);
  while (pq.size()) {
    int d = get<0>(pq.top()), f = get<1>(pq.top()), v = get<2>(pq.top());
    pq.pop();
    if (v == t) {
      cout << d << endl;
      return;
    }
    if (f < cap) { /* Add one unit of fuel */
      if (dp[v][f + 1] > d + price[v]) {
        dp[v][f + 1] = d + price[v];
        pq.emplace(dp[v][f + 1], f + 1, v);
      }
    }
    for (const auto &e : g[v]) {
      int u = e.first, nf = f - e.second;
      if (nf >= 0 and dp[u][nf] > d) {
        dp[u][nf] = d;
        pq.emplace(dp[u][nf], nf, u);
      }
    }
  }
  cout << "impossible" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> n >> m) {
    g.clear();
    g.resize(n);
    price.clear();
    price.resize(n);
    for (int i = 0; i < n; ++i)
      cin >> price[i];
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
      cin >> cap >> s >> t;
      dijkstra();
    }
  }
}