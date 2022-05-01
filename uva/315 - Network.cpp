#include <algorithm>
#include <ciso646>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int N;
vector<vector<int>> g;

void articulation_point(int u, int parent, int &ix, vector<int> &num,
                        vector<int> &low, vector<int> &bridges) {
  low[u] = num[u] = ix++;
  for (int i = 0; i < g[u].size(); ++i) {
    if (num[g[u][i]] == -1) {
      articulation_point(g[u][i], u, ix, num, low, bridges);
      if (low[g[u][i]] >= num[u])
        ++bridges[u];
      low[u] = min(low[u], low[g[u][i]]);
    } else if (g[u][i] != parent) {
      low[u] = min(low[u], num[g[u][i]]);
    }
  }
}

int num_bridges(const vector<vector<int>> &g) {
  int ix = 0;
  int n = g.size();
  vector<int> low(n, 0), num(n, -1), bridges(n, 0);
  articulation_point(0, -1, ix, num, low, bridges);
  if (bridges[0] > 0)
    --bridges[0];

  int res = 0;
  for (int i = 0; i < N; ++i)
    if (bridges[i] > 0)
      ++res;
  return res;
}

int main() {
  while (cin >> N, N != 0) {
    g.clear();
    g.resize(N);
    string s;

    while (getline(cin, s), s[0] != '0') {
      stringstream ss(s);
      int x;
      ss >> x;
      --x;
      int y;
      while (ss >> y) {
        --y;
        g[x].push_back(y);
        g[y].push_back(x);
      }
    }

    cout << num_bridges(g) << endl;
  }
}
