#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* Finding articulation points, but with some small details. The 'pigeon value'
 * is the number of connected components that the vertex removal leaves
 * the graph with. If there aren't M articulation points, then print the points
 * which aren't used in numerical order with 'pigeon value' equal to 1.*/

int N, M;
vector<vector<int>> g;
vector<int> index, low;
vector<bool> articulation_vertex;
vector<pair<int, int>> targets;
int root_children;
int ix;

void articulation_point(int u, int parent) {
  low[u] = index[u] = ix++;
  for (int i = 0; i < g[u].size(); ++i) {
    if (index[g[u][i]] == -1) {
      articulation_point(g[u][i], u);
      if (u == 0)
        ++root_children;
      if (low[g[u][i]] >= index[u])
        articulation_vertex[u] = true;
      low[u] = min(low[u], low[g[u][i]]);
    } else if (g[u][i] != parent) {
      low[u] = min(low[u], num[g[u][i]]);
    }
  }
}

void dfs(int v) {
  if (index[v] != -1)
    return;
  index[v] = 0;
  for (int i = 0; i < g[v].size(); ++i)
    dfs(g[v][i]);
}

int num_components(int v) {
  index.assign(N, -1);
  index[v] = 0;
  int components = 0;
  for (int i = 0; i < N; ++i) {
    if (index[i] == -1)
      ++components, dfs(i);
  }
  return components;
}

bool comp(const pair<int, int> &a, const pair<int, int> &b) {
  return a.second > b.second || a.second == b.second && a.first < b.first;
}

int main() {
  while (cin >> N >> M, N != 0) {
    g.clear();
    g.resize(N);
    int x, y;
    while (cin >> x >> y, x != -1) {
      g[x].push_back(y);
      g[y].push_back(x);
    }

    index.assign(N, -1);
    low.assign(N, -1);
    articulation_vertex.assign(N, false);
    ix = 0;

    articulation_point(0, -1);
    articulation_vertex[0] = root_children > 1;

    targets.clear();
    for (int i = 0; i < N; ++i) {
      if (articulation_vertex[i])
        targets.push_back(make_pair(i, num_components(i)));
    }

    index.assign(N, -1);
    sort(targets.begin(), targets.end(), comp);
    for (int i = 0; i < min(M, (int)targets.size()); ++i) {
      cout << targets[i].first << " " << targets[i].second << endl;
      index[targets[i].first] = 0;
    }

    for (int i = 0, m = M - targets.size(); m > 0; ++i) {
      if (index[i] == -1)
        --m, cout << i << " 1" << endl;
    }

    cout << endl;
  }
}