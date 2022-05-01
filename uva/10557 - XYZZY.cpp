#include <algorithm>
#include <ciso646>
#include <iostream>
#include <stack>
#include <vector>
#define INF 9999999

using namespace std;

/* Idea: run Bellman-Ford, but, first, change the sign of the edges, so that
 * negative-cycle detection becomes positive-cycle detection.
 *
 * Also, check if there is indeed a path between 'start' and 'finish', and,
 * if there's a cycle, check if it's indeed possible to reach it from 'start',
 * and reach 'end' from it.
 *
 * Something else: you can't relax an edge on Bellman-Ford if the new energy
 * is <= 0!
 * */

vector<vector<int>> g;
int N;

bool dfs(int s, const int t) {
  vector<bool> visited(N, false);
  stack<int> q;
  q.push(s);

  while (not q.empty()) {
    int v = q.top();
    q.pop();
    if (v == t)
      return true;
    if (visited[v])
      continue;
    visited[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
      if (not visited[g[v][i]])
        q.push(g[v][i]);
    }
  }
  return false;
}

int main() {
  while (true) {
    cin >> N;
    if (N == -1)
      break;

    g.clear();
    g.resize(N);
    vector<int> v(N);

    for (int i = 0; i < N; ++i) {
      cin >> v[i];
      v[i] = -v[i];
      int x;
      cin >> x;
      g[i].resize(x);
      for (int j = 0; j < x; ++j) {
        cin >> g[i][j];
        --g[i][j];
      }
    }

    if (not dfs(0, N - 1)) {
      cout << "hopeless" << endl;
      continue;
    }

    vector<int> dist(N, INF);
    dist[0] = -100;

    for (int i = 0; i < N - 1; ++i) {
      for (int u = 0; u < N; ++u) {
        for (int j = 0; j < g[u].size(); ++j) {
          int w = g[u][j];
          if (dist[u] + v[w] < 0)
            dist[w] = min(dist[u] + v[w], dist[w]);
        }
      }
    }

    bool cycle = false;
    for (int u = 0; u < N; ++u) {
      for (int j = 0; j < g[u].size(); ++j) {
        int w = g[u][j];
        if (dist[u] + v[w] < 0 and dist[w] > dist[u] + v[w]) {
          if (dfs(0, w) and dfs(w, N - 1)) {
            cycle = true;
          }
        }
      }
    }

    if (cycle == true or dist[N - 1] < 0) {
      cout << "winnable" << endl;
    } else {
      cout << "hopeless" << endl;
    }
  }
}