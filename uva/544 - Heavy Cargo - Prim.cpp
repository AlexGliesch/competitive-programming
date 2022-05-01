#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

int n, m, max_tons, s, t;
vector<vector<ii>> g, dag;
bool visited[210];

bool dfs(int v) {
  if (visited[v])
    return false;
  if (v == t)
    return true;
  visited[v] = true;
  for (int i = 0; i < dag[v].size(); ++i) {
    if (dfs(dag[v][i].second)) {
      max_tons = min(max_tons, dag[v][i].first);
      return true;
    }
  }
  return false;
}

void prim() {
  priority_queue<pair<int, ii>> pq;
  memset(visited, false, n);
  visited[0] = true;
  for (int i = 0; i < g[0].size(); ++i)
    pq.push(make_pair(g[0][i].first, make_pair(0, g[0][i].second)));

  while (pq.size()) {
    int w = pq.top().first, u = pq.top().second.second,
        p = pq.top().second.first;
    pq.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    dag[u].push_back(make_pair(w, p));
    dag[p].push_back(make_pair(w, u));
    for (int i = 0; i < g[u].size(); ++i) {
      if (!visited[g[u][i].second])
        pq.push(make_pair(g[u][i].first, ii(u, g[u][i].second)));
    }
  }

  memset(visited, false, n);
  max_tons = (1 << 28);
  dfs(s);
}

int main() {
  int scenario_counter = 1;
  while (cin >> n >> m, n != 0 && m != 0) {
    g.clear();
    g.resize(n);
    dag.clear();
    dag.resize(n);

    map<string, int> index;
    int index_counter = 0;
    for (int i = 0; i < m; ++i) {
      string s, t;
      cin >> s >> t;
      int w;
      cin >> w;
      if (index.count(s) == 0)
        index[s] = index_counter++;
      if (index.count(t) == 0)
        index[t] = index_counter++;
      g[index[s]].push_back(make_pair(w, index[t]));
      g[index[t]].push_back(make_pair(w, index[s]));
    }

    string ss, st;
    cin >> ss >> st;
    s = index[ss], t = index[st];

    prim();
    cout << "Scenario #" << scenario_counter++ << endl;
    cout << max_tons << " tons" << endl << endl;
  }
}