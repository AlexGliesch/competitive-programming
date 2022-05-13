class Solution {
public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
    vector<vector<int>> g(n);
    vector<vector<int>> ecolor(n);
    
    for (const auto& e : redEdges) {
      g[e[0]].push_back(e[1]);
      ecolor[e[0]].push_back(0);
    }
    for (const auto& e : blueEdges) {
      g[e[0]].push_back(e[1]);
      ecolor[e[0]].push_back(1);
    }
    
    vector<array<int, 2>> dist(n);
    for (auto& a : dist) a[0] = a[1] = -1;
    
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    dist[0][1] = 0;
    q.emplace(0, -1);
    
    while (q.size()) {
      int v = q.front().first, color = q.front().second;
      q.pop();
      for (int i = 0; i < g[v].size(); ++i)  {
        int u = g[v][i], c = ecolor[v][i];
        if ((color == -1 || c == 1 - color) and dist[u][c] == -1) {
          dist[u][c] = color == -1 ? 1 : dist[v][color] + 1;
          q.emplace(u, c);          
        } 
      }
    }
    
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      if (dist[i][0] == -1 and dist[i][1] == -1) ans[i] = -1;
      else if (dist[i][0] == -1) ans[i] = dist[i][1];
      else if (dist[i][1] == -1) ans[i] = dist[i][0];
      else ans[i] = min(dist[i][0], dist[i][1]);
    }
    return ans;
  }
};