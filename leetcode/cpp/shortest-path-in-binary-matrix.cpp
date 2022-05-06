class Solution {
public:
  int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    if (grid[0][0] == 1) return -1;
    int n = grid.size();
    vector<int> dist(n * n, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 1;
    while (q.size()) {
      int v = q.front();
      q.pop();
      int r = v / n, c = v % n;
      if (r == c && r == n - 1) return dist[v];
      int dr[8] = {-1, 1, -1, 1, -1, 1, 0, 0},
          dc[8] = {0, 0, -1, 1, 1, -1, 1, -1};
      for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i], nc = c + dc[i];
        int u = nr * n + nc;
        if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0 &&
            dist[u] == -1) {
          dist[u] = dist[v] + 1;
          q.push(u);
        }
      }
    }
    return -1;
  }
};