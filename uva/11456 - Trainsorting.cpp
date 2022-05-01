#include <algorithm>
#include <iostream>

using namespace std;

/* Print max(LDS(i) + LIS(i) - 1) for all i in [N]. I didn`t understand exactly
 * why: go the solution from a blog.
 *
 * Smart detail: LDS and LIS can be done in the same for loop (O(n^2) version).
 * Don't forget LIS's array starts from 1. */

int N;
int w[2010], lis[2010], lds[2010];

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N;
    for (int i = 0; i < N; ++i)
      cin >> w[i];

    for (int i = N - 1; i >= 0; --i) {
      lis[i] = lds[i] = 1;
      for (int j = i + 1; j < N; ++j) {
        if (w[j] < w[i])
          lis[i] = max(lis[i], 1 + lis[j]);
        else
          lds[i] = max(lds[i], 1 + lds[j]);
      }
    }

    int res = 0;
    for (int i = 0; i < N; ++i)
      res = max(res, lis[i] + lds[i] - 1);

    cout << res << endl;
  }
}