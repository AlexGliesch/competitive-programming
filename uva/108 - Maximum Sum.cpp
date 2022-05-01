#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

/* idea: for each sub-matrix starting from (0, 0), store the sum of all the
 * elements in a dp.
 *
 * this can be done easily when you create the matrix: the partial sum of a
 * submatrix (i, j) is the element (i, j) + the partial sums of the matrices
 * (i-1, j) and (i, j-1), minus the partial sum of matrix (i-1, j-1) (because
 * you added it twice).
 *
 * then, for each sub-matrix starting from (0, 0), and for each sub-matrix
 * inside that one starting from (0, 0), find the difference between their
 * sums: it will be the sum of the sub matrix correspondent to the difference
 * in elements between them.
 * */

int m[105][105], n;

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> m[i][j];
      if (i > 0)
        m[i][j] += m[i - 1][j];
      if (j > 0)
        m[i][j] += m[i][j - 1];
      if (i * j > 0)
        m[i][j] -= m[i - 1][j - 1];
    }
  }

  int res = -INT_MAX;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < i; ++k) {
        for (int l = 0; l < j; ++l) {
          int r = m[i][j];
          /* remove the sides */
          if (k > 0)
            r -= m[k - 1][j];
          if (l > 0)
            r -= m[i][l - 1];
          /* if we removed both sides, we removed the top left sub-
           * matrix twice. add it once again so the result is
           * correct.*/
          if (l * k > 0)
            r += m[k - 1][l - 1];
          res = max(res, r);
        }
      }
    }
  }

  cout << res << endl;
}