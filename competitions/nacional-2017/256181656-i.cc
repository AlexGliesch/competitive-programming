#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {

  int n, r;

  cin >> n >> r;

  vector<vector<pair<int, int> > > g(n);
  for (int i = 0; i < r; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    g[a].push_back(make_pair(b, c));
    g[b].push_back(make_pair(a, c));
  }

  int m;
  cin >> m;
  for (int t = 0; t < m; t++) {
    int s1, s2;
    cin >> s1 >> s2;
    s1--;
    s2--;
    vector<bool> visited(n, false);
    visited[s1] = true;
    visited[s2] = true;

    int cost = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    for (int i = 0; i < g[s1].size(); i++)
    {
      pq.push(make_pair(g[s1][i].second, g[s1][i].first));
      if (g[s1][i].first == s2)
        cost += g[s1][i].second;
    }
    for (int i = 0; i < g[s2].size(); i++)
      pq.push(make_pair(g[s2][i].second, g[s2][i].first));
    
    while (pq.size()) {
      int u = pq.top().second;
      int w = pq.top().first;
      pq.pop();
      if (visited[u]) continue;
      visited[u] = true;
      cost += w;
      for (int i = 0; i < g[u].size(); ++i)
      {
        int v = g[u][i].first;
        if (not visited[v])
            pq.push(make_pair(g[u][i].second, v));
      }
      
        

    
    }
    cout << cost << endl;
  }

  return 0;
}
