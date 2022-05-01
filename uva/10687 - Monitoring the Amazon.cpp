#include <cstring>
#include <iostream>

using namespace std;

/* Create the graph and do a dfs to test if it's possible to reach every
 * node from node 0. */

int N, pos[1010][2], g[1010][2], num_visited;
bool visited[1010];

int dist_sq(int *a, int *b) {
  return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
}

bool comp(int *a, int *b, int *rel) {
  int da = dist_sq(a, rel), db = dist_sq(b, rel);
  if (da == db)
    return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
  return da < db;
}

bool dfs(int v) {
  if (visited[v])
    return false;
  visited[v] = true, ++num_visited;
  dfs(g[v][0]), dfs(g[v][1]);
  return num_visited == N;
}

int main() {
  while (cin >> N, N != 0) {
    for (int i = 0; i < N; ++i)
      cin >> pos[i][0] >> pos[i][1];

    memset(g, -1, sizeof g);
    memset(visited, false, sizeof visited);
    num_visited = 0;

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (i == j)
          continue;
        if (comp(pos[j], pos[g[i][0]], pos[i]) || g[i][0] == -1) {
          g[i][1] = g[i][0];
          g[i][0] = j;
        } else if (comp(pos[j], pos[g[i][1]], pos[i]) || g[i][1] == -1) {
          g[i][1] = j;
        }
      }
    }

    cout << (dfs(0) ? "All stations are reachable."
                    : "There are stations that are unreachable.")
         << endl;
  }
}