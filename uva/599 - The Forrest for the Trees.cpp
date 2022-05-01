#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

map<char, int> index;
vector<vector<int>> g;
vector<bool> visited;

void dfs(char v) {
  if (visited[v])
    return;
  visited[v] = true;
  for (int i = 0; i < g[v].size(); ++i)
    dfs(g[v][i]);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    char c;
    vector<pair<char, char>> edges;
    while (cin >> c, c != '*') {
      cin >> c;
      char x = c;
      cin >> c >> c;
      edges.push_back(make_pair(x, c));
      cin >> c;
    }

    index.clear();
    string s;
    getline(cin, s);
    getline(cin, s);
    istringstream ss(s);
    int n = 0;
    while (ss >> c) {
      if (c == ',')
        continue;
      index[c] = n++;
    }
    g.clear();
    g.resize(n);
    for (int i = 0; i < edges.size(); ++i) {
      g[index[edges[i].first]].push_back(index[edges[i].second]);
      g[index[edges[i].second]].push_back(index[edges[i].first]);
    }

    visited.assign(n, false);
    int trees = 0, acorns = 0;
    for (int i = 0; i < n; ++i) {
      if (visited[i])
        continue;
      g[i].empty() ? ++acorns : ++trees;
      dfs(i);
    }

    cout << "There are " << trees << " tree(s) and " << acorns << " acorn(s)."
         << endl;
  }
}