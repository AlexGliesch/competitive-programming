#include "includes.h"

class Solution {
  void sortDiag(const int ri, const int ci, const int R, const int C,
                vector<vector<int>>& mat) {
    int r = ri, c = ci;
    vector<int> v;
    while (r < R && c < C) {
      v.push_back(mat[r][c]);
      ++r, ++c;
    }
    sort(begin(v), end(v));
    r = ri, c = ci;
    int j = 0;
    while (r < R && c < C) {
      mat[r][c] = v[j];
      ++j, ++r, ++c;
    }
  }

public:
  vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
    // diagonals starting from top row
    int R = mat.size();
    int C = mat[0].size();

    for (int i = 0; i < mat[0].size(); ++i) {
      sortDiag(0, i, R, C, mat);
    }
    // diagonals starting from left column
    for (int i = 1; i < mat.size(); ++i) {
      sortDiag(i, 0, R, C, mat);
    }

    // return the matrix
    return mat;
  }
};
