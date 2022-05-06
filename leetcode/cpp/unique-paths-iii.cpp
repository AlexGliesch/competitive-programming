// For some reason I had to use 2 pruning rules in order to pass TLE:
// 1. if a move splits reachable tiles into 2 or more cc's, prune
// 2. if a free tile (0) has only one non-obstacle neighbor, prune (dead-end)
//
// To be honest, I think a good implementation should be able to pass without
// these pruning rules.

const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};

class Solution {
public:
  vector<vector<int>> grid;
  int R, C;
  int numFree;

  bool posOk(int r, int c) { return !(r < 0 || r >= R || c < 0 || c >= C); }

  bool bitOn(int mask, int r, int c) { return mask & (1 << (r * C + c)); }

  bool prune(int mask, int vis) {
    int vbfs = mask;
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c) {
        // Dead end pruning
        if (grid[r][c] == 0 && !bitOn(mask, r, c)) {
          int numReachable = 0;
          for (int d = 0; d < 4; ++d) {
            int rr = r + dr[d], cc = c + dc[d];
            if (posOk(rr, cc))
              numReachable += grid[rr][cc] != -1 && !bitOn(mask, rr, cc);
          }
          if (numReachable <= 1) return false;
        }
        // CC pruning
        if (grid[r][c] != -1 && !bitOn(vbfs, r, c)) {
          vbfs = vbfs | (1 << (r * C + c));
          int numVbfs = vis + 1;
          queue<int> q;
          q.push(r * C + c);
          while (q.size()) {
            int v = q.front();
            q.pop();
            int r = v / C, c = v % C;
            for (int d = 0; d < 4; ++d) {
              int rr = r + dr[d], cc = c + dc[d];
              if (!posOk(rr, cc) || grid[rr][cc] == -1 || bitOn(vbfs, rr, cc))
                continue;
              vbfs = vbfs | (1 << (rr * C + cc));
              ++numVbfs;
              q.push(rr * C + cc);
            }
          }
          if (numVbfs != numFree) return false;
          return numVbfs != numFree;
        }
      }
    return false;
  }

  int paths(int r, int c, int mask, int vis) {
    if (grid[r][c] == 2) {
      return vis == numFree;
    }
    if (prune(mask, vis)) return 0; 

    int ans = 0;
    for (int d = 0; d < 4; ++d) {
      int rr = r + dr[d], cc = c + dc[d];
      if (posOk(rr, cc) && !bitOn(mask, rr, cc) && grid[rr][cc] != -1) {
        ans += paths(rr, cc, mask | (1 << (rr * C + cc)), vis + 1);
      }
    }
    return ans; 
  }

  int uniquePathsIII(vector<vector<int>>& grid) {
    this->grid = grid;
    R = grid.size(), C = grid[0].size();
    numFree = 0;
    int rs, cs;
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c) {
        numFree += grid[r][c] != -1;
        if (grid[r][c] == 1) rs = r, cs = c;
      }
    return paths(rs, cs, 1 << (rs * C + cs), 1);
  }
};