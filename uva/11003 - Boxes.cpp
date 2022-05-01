#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/* Just generate the recurrence and store the states. The load factor is always
 * the smallest load factor found so far. */

int N, w[1010], ld[1010], dp[1010][3010];

int stack(int i, int cur_ld) {
  if (i == N)
    return 0;
  if (dp[i][cur_ld] == -1) {
    if (w[i] > cur_ld)
      dp[i][cur_ld] = stack(i + 1, cur_ld);
    else
      dp[i][cur_ld] = max(1 + stack(i + 1, min(ld[i], cur_ld - w[i])),
                          stack(i + 1, cur_ld));
  }
  return dp[i][cur_ld];
}

int main() {
  while (cin >> N, N != 0) {
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < N; ++i)
      cin >> w[i] >> ld[i];

    int res = 0;
    for (int i = 0; i < N - 1; ++i)
      res = max(res, stack(i + 1, ld[i]));
    cout << res + 1 << endl;
  }
}