class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    auto b2 = board;
    int R = board.size(), C = board[0].size();

    // could be optimized to iterate over memory contiguously...
    int dr[8] = {-1, 1, -1, 1, -1, 1, 0, 0},
        dc[8] = {0, 0, -1, 1, 1, -1, 1, -1};
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c) {
        int liveNbs = 0;
        for (int i = 0; i < 8; ++i) {
          int nr = r + dr[i], nc = c + dc[i];
          if (nr >= 0 && nr < R && nc >= 0 && nc < C)
            liveNbs += board[r + dr[i]][c + dc[i]];
        }
        bool live = board[r][c];
        if (live && liveNbs < 2)
          b2[r][c] = 0;
        else if (live && (liveNbs == 2 || liveNbs == 3))
          b2[r][c] = 1;
        else if (live && liveNbs > 3)
          b2[r][c] = 0;
        else if (!live && liveNbs == 3)
          b2[r][c] = 1;
      }
    swap(board, b2);
  }
};