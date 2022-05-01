#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<int> in, num_paths, num_visited;

void count_paths() {
  queue<int> q;
  q.push(0);
  num_paths[0] = 1;
  while (q.size()) {
    int v = q.front();
    q.pop();
    for (auto u : g[v]) {
      num_paths[u] += num_paths[v];
      num_visited[u] += num_visited[v] + num_paths[v];
      num_paths[u] %= 100000;
      num_visited[u] %= 100000;
      if (--in[u] == 0)
        q.push(u);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> n >> m;
    g.clear();
    g.resize(n);
    num_visited.assign(n, 0);
    num_paths.assign(n, 0);
    in.assign(n, 0);

    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      ++in[v];
    }

    count_paths();
    cout << "Case " << t + 1 << ": " << num_visited[n - 1] << ' '
         << num_paths[n - 1] << endl;
  }
}