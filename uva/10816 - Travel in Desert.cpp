#include <algorithm>
#include <ciso646>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* Run Dijsktra twice: once in order to find the minimum temperature, and
 * another one in order to find the minimum distance. For the second one,
 * ignore edges that are hottest than the minimum temperature found on
 * the first one. */

typedef pair<pair<double, double>, int> Edge;

int main() {
  int V, E, S, T;
  while (cin >> V >> E >> S >> T) {
    vector<vector<Edge>> g(V);
    for (int i = 0; i < E; ++i) {
      int x, y;
      cin >> x >> y;
      double t, d;
      cin >> t >> d;
      g[x - 1].push_back(make_pair(make_pair(t, d), y - 1));
      g[y - 1].push_back(make_pair(make_pair(t, d), x - 1));
    }
    --S, --T;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<double> dist(V, 9999999), temp(V, 9999999);
    dist[S] = temp[S] = 0;

    pq.push(make_pair(make_pair(0, 0), S));

    while (pq.size()) {
      Edge e = pq.top();
      pq.pop();
      int v = e.second;
      double t = e.first.first;
      if (temp[v] != t)
        continue;
      if (v == T)
        break;
      for (int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i].second;
        if (temp[u] > max(t, g[v][i].first.first)) {
          temp[u] = max(t, g[v][i].first.first);
          pq.push(make_pair(make_pair(temp[u], 0), u));
        }
      }
    }

    vector<int> parent(V, -1);
    pq.push(make_pair(make_pair(0, 0), S));
    while (pq.size()) {
      Edge e = pq.top();
      pq.pop();
      int v = e.second;
      double d = e.first.second;
      if (dist[v] != d)
        continue;
      if (v == T)
        break;
      for (int i = 0; i < g[v].size(); ++i) {
        if (g[v][i].first.first > temp[T])
          continue;
        int u = g[v][i].second;
        if (dist[u] > d + g[v][i].first.second) {
          dist[u] = d + g[v][i].first.second;
          parent[u] = v;
          pq.push(make_pair(make_pair(0, dist[u]), u));
        }
      }
    }

    vector<int> path;
    int v = T;
    while (v != S) {
      path.push_back(v + 1);
      v = parent[v];
    }
    cout << S + 1 << " ";
    for (int i = path.size() - 1; i >= 1; --i)
      cout << path[i] << " ";
    cout << T + 1 << endl;
    cout << setprecision(1) << fixed;
    cout << dist[T] << " " << temp[T] << endl;
  }
}