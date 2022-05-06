#include "includes.h"

class Solution {
public:
  bool isDiagToeplitz(int r, int c, int R, int C,
                      const vector<vector<int>>& matrix) {
    unordered_set<int> nums;
    while (r < R && c < C) {
      nums.insert(matrix[r][c]);
      ++r, ++c;
    }
    return !(nums.size() > 1);
  }

  bool isToeplitzMatrix(vector<vector<int>>& matrix) {
    const int R = matrix.size(), C = matrix[0].size();
    for (int ci = 0; ci < C; ++ci) {
      if (!isDiagToeplitz(0, ci, R, C, matrix)) return false;
    }
    for (int ri = 0; ri < R; ++ri) {
      if (!isDiagToeplitz(ri, 0, R, C, matrix)) return false;
    }
    return true;
  }
};
