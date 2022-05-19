class Solution {
public:
  int bfs(int sr, int sc, int tr, int tc, const vector<vector<int>>& F) {     
    vector<vector<int>> dist(F.size(), vector<int>(F[0].size(), INT_MAX));
    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    dist[sr][sc] = 0;
    while (q.size()) {
      int r = q.front().first, c = q.front().second;
      q.pop();
      if (r == tr && c == tc) return dist[r][c];
      int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
      for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < F.size() && nc >= 0 && nc < F[0].size()
            && dist[nr][nc] == INT_MAX && F[nr][nc] != 0) {
          dist[nr][nc] = dist[r][c] + 1;
          q.emplace(nr, nc);
        }
      }      
    }
    return INT_MAX;
  }
  
  int cutOffTree(vector<vector<int>>& F) {    
    vector<pair<int, pair<int, int>>> v;
    if (F[0][0] == 0) return -1;
    v.emplace_back(1, pair(0, 0));
    for (int r = 0; r < F.size(); ++r) 
      for (int c = 0; c < F[0].size(); ++c)
        if (F[r][c] > 1) v.emplace_back(F[r][c], pair(r, c));
    sort(begin(v), end(v));
    int ans = 0;
    for (int i = 1; i < v.size(); ++i) {
      int dist = bfs(v[i-1].second.first, v[i-1].second.second, 
                     v[i].second.first, v[i].second.second,
                     F);
      if (dist == INT_MAX)
        return -1;
      ans += dist;
    }
    return ans;
  }
};