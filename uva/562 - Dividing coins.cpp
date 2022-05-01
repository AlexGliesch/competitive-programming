#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/* idea: find all possible achievable values until sum / 2. that is, all the
 * values <= sum / 2 that can be achievable by any combination of coin choices.
 * this uses the suposition that the sum of all elements will be small enough
 * to be stored in memory.
 *
 * by giving the greatest of those values to both the guys, and then giving
 * the rest (the difference, which will be sum - 2 * largest) to one of them.
 * */

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int k = 0; k < n; ++k) {
    int m;
    cin >> m;
    vector<int> coins(m + 1);
    for (int i = 0; i < m; ++i)
      cin >> coins[i];

    int sum = accumulate(coins.begin(), coins.end(), 0);

    vector<bool> dp(1 + sum / 2, false);
    dp[0] = true;

    for (int i = 0; i < m; ++i) {
      auto dp2 = dp;
      for (int j = 0; j + coins[i] <= sum / 2; ++j)
        if (dp2[j])
          dp[j + coins[i]] = true;
    }

    for (int i = sum / 2; i >= 0; --i)
      if (dp[i]) {
        cout << sum - 2 * i << endl;
        break;
      }
  }
}
