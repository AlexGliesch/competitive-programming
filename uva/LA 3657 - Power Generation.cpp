#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* Solved using dfs: repeatedly send energy from the leaves to the internal
 * nodes until some node reaches minimal energy. */

vector<vector<int>> g;
vector<int> p;
vector<bool> visited;
int result;
int N, C;

int dist(const pair<int, int> &a, const pair<int, int> &b) {
  return (a.first - b.first) * (a.first - b.first) +
         (a.second - b.second) * (a.second - b.second);
}

int dfs(int v) {
  visited[v] = true;
  int power = p[v];
  for (int i = 0; i < g[v].size(); ++i) {
    if (not visited[g[v][i]]) {
      power += dfs(g[v][i]);
    }
  }
  if (power >= C) {
    ++result;
    return 0;
  } else {
    return power;
  }
}

int main() {
  while (true) {
    cin >> N >> C;
    if (N == 0 and C == 0)
      break;
    g.clear();
    g.resize(N);
    p.clear();
    p.resize(N);
    visited.clear();
    visited.resize(N, false);
    result = 0;

    vector<pair<int, int>> coords(N);
    cin >> coords[0].first >> coords[0].second >> p[0];

    for (int i = 1; i < N; ++i) {
      cin >> coords[i].first >> coords[i].second >> p[i];
      int closest = -1, minDist = (1 << 30), closestCount = 0;
      for (int j = 0; j < i; ++j) {
        int d = dist(coords[i], coords[j]);
        if (d < minDist) {
          closest = j;
          minDist = d;
          closestCount = 0;
        } else if (d == minDist) {
          ++closestCount;
        }
      }
      if (closestCount > 1)
        closest = 0;
      g[i].push_back(closest);
      g[closest].push_back(i);
    }

    dfs(0);
    cout << result << endl;
  }
}