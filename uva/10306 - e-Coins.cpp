#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/* coin change: do a dp[i][j] where i is the current conventional sum and
 * j is the current info sum. if s^2 = i*i + j*j return 0,
 * if s^2 > i*i + j*j return INF, otherwise,
 * return 1 + min(change(i + conv[k], j + info[k])) for each k in [m] */

int m, s, conv[45], info[45], dp[300][300];

int coin_change(int sum_conv, int sum_info) {
  int val = sum_conv * sum_conv + sum_info * sum_info;
  if (val > s)
    return (1 << 29);
  if (val == s)
    return 0;
  if (dp[sum_conv][sum_info] != -1)
    return dp[sum_conv][sum_info];
  int res = (1 << 29);
  for (int i = 0; i < m; ++i) {
    res = min(res, 1 + coin_change(sum_conv + conv[i], sum_info + info[i]));
  }
  return dp[sum_conv][sum_info] = res;
}

int main() {
  int n;
  cin >> n;
  for (int t = 0; t < n; ++t) {
    memset(dp, -1, sizeof dp);
    cin >> m >> s;
    s *= s;
    for (int i = 0; i < m; ++i)
      cin >> conv[i] >> info[i];
    int res = coin_change(0, 0);
    if (res < (1 << 29))
      cout << res << endl;
    else
      cout << "not possible" << endl;
  }
}