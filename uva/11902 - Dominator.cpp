#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

/* First, do a dfs to see which nodes are reachable from node 0.
 * For every node v, do a dfs ignoring that node; for each node u that was
 * reachable before and is not rechable after (without v), then v dominates u.
 *
 * Note that the graph can be disconnected, so nodes which aren't reachable
 * from 0 aren't dominated by 0 nor by themselves. */

vector<vector<int>> g;
vector<vector<bool>> dom;
int N;

void dfs(int v, vector<bool> &visited) {
  if (visited[v])
    return;
  visited[v] = true;

  for (int i = 0; i < g[v].size(); ++i)
    dfs(g[v][i], visited);
}

int main() {
  int T;
  cin >> T;

  for (int t = 0; t < T; ++t) {
    cin >> N;

    g.assign(N, vector<int>());
    for (int v = 0; v < N; ++v) {
      for (int u = 0; u < N; ++u) {
        int x;
        cin >> x;
        if (x == 1)
          g[v].push_back(u);
      }
    }

    vector<bool> visited_before(N, false);
    dfs(0, visited_before);

    dom.assign(N, vector<bool>(N, false));
    for (int v = 0; v < N; ++v) {
      vector<bool> visited_after(N, false);
      visited_after[v] = true;
      dfs(0, visited_after);
      for (int u = 0; u < N; ++u) {
        dom[v][u] = visited_before[u] and not visited_after[u];
      }
      dom[v][v] = visited_before[v];
    }

    cout << "Case " << 1 + t << ":" << endl;
    for (int v = 0; v < N; ++v) {
      cout << "+";
      for (int j = 0; j < 2 * N - 1; ++j)
        cout << "-";
      cout << "+" << endl;
      for (int j = 0; j < N; ++j)
        cout << "|" << (dom[v][j] ? "Y" : "N");
      cout << "|" << endl;
    }
    cout << "+";
    for (int j = 0; j < 2 * N - 1; ++j)
      cout << "-";
    cout << "+" << endl;
  }
}