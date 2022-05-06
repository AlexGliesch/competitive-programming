class Solution {
public:
  int maximumMinimumPath(vector<vector<int>>& grid) {
    int R = grid.size(), C = grid[0].size();
    priority_queue<pair<int, pair<int, int>>> pq;
    vector<vector<int>> dist(R, vector<int>(C, -1));
    dist[0][0] = grid[0][0];
    pq.emplace(dist[0][0], pair(0, 0));
    while (pq.size()) {
      int r = pq.top().second.first, c = pq.top().second.second;
      if (dist[r][c] != pq.top().first) continue;
      pq.pop();
      if (r == R - 1 && c == C - 1) return dist[r][c];

      int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
      for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
          int nd = min(grid[nr][nc], dist[r][c]);
          assert(nd >= 0);
          if (dist[nr][nc] < nd) {
            dist[nr][nc] = nd;
            pq.emplace(dist[nr][nc], pair(nr, nc));
          }
        }
      }
    }
    assert(false);
    return -1; // should never happen
  }
};