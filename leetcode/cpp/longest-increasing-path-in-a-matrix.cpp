class Solution {
private:
  // dfs(r, c)
  // ans = 1
  // if dp[r][c] != -1
  //  return dp[r][c]
  // for (nr, nc) in N(r,c) s.t. m[nr][nc] > m[r][c] and s.t. !visited[nr][nc]
  //  visited[nr][nc] = true
  //  ans = max(ans, 1 + rec(nr, nc))
  //  visited[nr][nc] = false
  // return dp[r][c] = ans
  
  vector<vector<int>> m;
  vector<vector<int>> dp;
  vector<vector<bool>> visited;
  int R, C;
  
  int dfs(int r, int c) {
    if (dp[r][c] != -1) 
      return dp[r][c];
    
    int ans = 1;
    visited[r][c] = true;
    constexpr int dr[] = { 0, 0, -1, 1 }, dc[] = { -1, 1, 0, 0 };
    for (int i = 0; i < 4; ++i) {
      int nr = r + dr[i], nc = c + dc[i];
      if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
      if (visited[nr][nc] || m[nr][nc] <= m[r][c]) continue;      
      ans = max(ans, 1 + dfs(nr, nc));      
    }
    visited[r][c] = false;
    return dp[r][c] = ans;
  }
  
public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    m = matrix;
    R = m.size(), C = m[0].size();
    dp.assign(R, vector<int>(C, -1));
    visited.assign(R, vector<bool>(C, false));
    int ans = 0;
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c)
        ans = max(ans, dfs(r, c));
    return ans;
  }
};

// [[1]]
//
// [[1, 2, 3],
//  [4, 5, 6],
//  [7, 8, 9]]
//
// [[1, 2]]
//
// [[1, 1]]
//
// [[1, 1, 1],
//  [1, 1, 1],
//  [1, 1, 1]]
//
// [[1, 2, 3], 
//  [6, 5, 4],
//  [7, 8, 9]]
//
// [[1, 2, 999], 
//  [6, 5, 999],
//  [7, 8, 8]]
//