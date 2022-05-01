#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>
#define INF 9999999

/* Just run Bellman-Ford and check for cycles. */

using namespace std;
typedef pair<int, int> ii;

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, m;
    cin >> N >> m;

    vector<vector<ii>> g(N);
    vector<int> dist(N, INF);

    for (int i = 0; i < m; ++i) {
      int x, y, t;
      cin >> x >> y >> t;
      g[x].push_back(make_pair(y, t));
    }

    dist[0] = 0;

    bool has_cycle = false;
    for (int i = 0; i < N; ++i) {
      has_cycle = false;
      for (int u = 0; u < N; ++u) {
        for (int j = 0; j < g[u].size(); ++j) {
          const ii &e = g[u][j];
          if (dist[e.first] > dist[u] + e.second) {
            dist[e.first] = dist[u] + e.second;
            has_cycle = true;
          }
        }
      }
    }

    cout << (has_cycle ? "possible" : "not possible") << endl;
  }
}