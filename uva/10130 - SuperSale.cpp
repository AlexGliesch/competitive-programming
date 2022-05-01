#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/*
* each person in the family is a single knapsack problem.
* so you must solve knapsack for each person and add the results.
*
* knapsack works like this (page 108 of 'competitive programming')
* 1. val(id, 0) = 0 -> if remW = 0, we cannot take anything else
*
* 2. val(n, remW) = 0 -> if id = n, we have considered all items
*
* 3. if W[id] > remW, we have no choice but to ignore this item
*   val(id, remW) = val(id + 1, remW)
*
* 4. if W[id] <= remW, we have two choices: ignore or take this item;
*                                           we take the maximum
*    val(id, remW) = max(val(id + 1, remW), V[id] + val(id + 1, remW - W[id]))
*
*/

int T, N, G, dp[1010][35], p[1010], w[1010], cap[110];

int knapsack(int i, int remW) {
  if (remW <= 0)
    return 0;
  if (i >= N)
    return 0;
  if (dp[i][remW] == -1) {
    if (w[i] > remW) {
      dp[i][remW] = knapsack(i + 1, remW);
    } else {
      dp[i][remW] =
          max(knapsack(i + 1, remW), p[i] + knapsack(i + 1, remW - w[i]));
    }
  }
  return dp[i][remW];
}

int main() {
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> p[i];
      cin >> w[i];
    }
    cin >> G;
    int ans = 0;
    for (int i = 0; i < G; ++i) {
      int MW;
      cin >> MW;
      memset(dp, -1, sizeof dp);
      ans += knapsack(0, MW);
    }
    cout << ans << endl;
  }
}
