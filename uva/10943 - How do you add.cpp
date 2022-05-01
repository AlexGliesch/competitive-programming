#include <ciso646>
#include <cstring>
#include <iostream>

using namespace std;
using ll = long long;

/*
 * the recurrence i used is how-many-ways(k, i), where:
 * k is the number of numbers left to pick up
 * i is the sum that must be achieved.
 *
 * how-many-ways(k, 0) = 1, if k > 0. there is only 1 way to pick numbers that
 * sum 0, and that is by picking the number 0.
 *
 * how-many-ways(1, i) = 1. there is only 1 way to pick 1 number that sums to i,
 * which is by picking i itself.
 *
 * how-many-ways(k, i) = sum(how-many-ways(k-1, i-j)), for 0 <= j <= i.
 * that is, we can pick any number between 0 and i (assuring i will still be
 * >= 0), and check how many ways we can achieve i-j by picking k-1.
 *
 * of course, in this case, the recurrence starts with (K, N).
 *
 * */

ll N, K, dp[110][110];

ll how(ll k, ll i /* how much is left (start with n)*/) {
  if (k > 0 and i == 0 or k == 1)
    return 1;
  if (dp[k][i] == -1) {
    dp[k][i] = 0;
    for (ll j = 0; j <= i; ++j) {
      dp[k][i] += how(k - 1, i - j);
      dp[k][i] %= 1000000;
    }
  }
  return dp[k][i];
}

int main() {
  while (cin >> N >> K, N and K) {
    memset(dp, -1, sizeof dp);
    cout << how(K, N) << endl;
  }
}