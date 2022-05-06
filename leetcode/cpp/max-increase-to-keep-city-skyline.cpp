// Description is very confusing.
// Only understood the actual problem after examining the 1st test case.

class Solution {
public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    int n = grid.size();

    // 0 left 1 right 2 top 3 bottom
    array<vector<vector<int>>, 4> sklDir;
    for (int d = 0; d < 4; ++d)
      sklDir[d].assign(n, vector<int>(n, -1));

    for (int d = 0; d < 4; ++d) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          int r[4] = {i, i, j, n - 1 - j};
          int c[4] = {j, n - 1 - j, i, i};
          int prr[4] = {r[d], r[d], r[d] - 1, r[d] + 1};
          int prc[4] = {c[d] - 1, c[d] + 1, c[d], c[d]};
          int prv;
          if (prr[d] < 0 || prr[d] >= n || prc[d] < 0 || prc[d] >= n)
            prv = -1;
          else {
            prv = sklDir[d][prr[d]][prc[d]];
            assert(prv != -1);
          }
          sklDir[d][r[d]][c[d]] = max(prv, grid[r[d]][c[d]]);
          // cout << "skl d=" << d << ", p=(" << r[d] << ", " << c[d] << ") -- "
          // << sklDir[d][r[d]][c[d]] << endl;
        }
      }
    }
    int ans = 0;
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        int up = numeric_limits<int>::max();
        up = max(0, min(max(sklDir[0][r][c], sklDir[1][r][c]),
                        max(sklDir[2][r][c], sklDir[3][r][c])) -
                        grid[r][c]);
        ans += up;
        // cout << "up " << r << ',' << c << '=' << up << endl;
      }
    }
    return ans;
  }
};