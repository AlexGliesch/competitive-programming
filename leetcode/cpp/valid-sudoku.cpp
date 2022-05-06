class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    vector<int> fr(10, 0);
    for (int i = 0; i < 9; ++i) {
      fr.assign(10, 0);
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') continue;
        ++fr[board[i][j] - '0'];
        if (fr[board[i][j] - '0'] > 1) return false;
      }

      fr.assign(10, 0);
      for (int j = 0; j < 9; ++j) {
        if (board[j][i] == '.') continue;
        ++fr[board[j][i] - '0'];
        if (fr[board[j][i] - '0'] > 1) return false;
      }
      // 0 1 2
      // 3 4 5
      // 6 7 8
      fr.assign(10, 0);
      int osr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
      int osc[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
      for (int j = 0; j < 9; ++j) {
        int ii = 3 * (i / 3) + (j / 3), jj = 3 * (i % 3) + (j % 3);
        if (board[ii][jj] == '.') continue;
        ++fr[board[ii][jj] - '0'];
        if (fr[board[ii][jj] - '0'] > 1) return false;
      }
    }

    return true;
  }
};