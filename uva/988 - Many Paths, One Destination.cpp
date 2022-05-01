#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
vector<vector<int>> g;
vector<int> in, num_paths;

void count_paths() {
  queue<int> q;
  q.push(0);
  num_paths[0] = 1;
  while (q.size()) {
    int v = q.front();
    q.pop();
    for (auto u : g[v]) {
      num_paths[u] += num_paths[v];
      if (--in[u] == 0)
        q.push(u);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int num_case = 0;
  while (cin >> n) {
    if (num_case++)
      cout << endl;
    g.clear();
    g.resize(n);
    in.assign(n, 0);
    num_paths.assign(n, 0);

    for (int v = 0; v < n; ++v) {
      int e;
      cin >> e;
      g[v].resize(e);
      for (auto &u : g[v]) {
        cin >> u;
        ++in[u];
      }
    }

    count_paths();
    int ans = 0;
    for (int v = 0; v < n; ++v)
      if (g[v].empty())
        ans += num_paths[v];
    cout << ans << endl;
  }
}