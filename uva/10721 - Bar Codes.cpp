#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

/* DP, simple. Just do the recurrence and memoize. */

/* K bars, N units, at most M units wide */
int N, K, M;
ull dp[51][51][51];

ull rec(int n, int k, int m) {
  if (dp[n][k][m] == -1) {
    if (k > K)
      dp[n][k][m] = 0;
    else if (n == N)
      dp[n][k][m] = (k == K) ? 1 : 0;
    else if (m >= M)
      dp[n][k][m] = rec(n + 1, k + 1, 1);
    else
      dp[n][k][m] = rec(n + 1, k + 1, 1) + rec(n + 1, k, m + 1);
  }
  return dp[n][k][m];
}

int main() {
  string buf;
  while (getline(cin, buf)) {
    stringstream ss(buf);
    ss >> N >> K >> M;
    memset(dp, -1, sizeof dp);
    cout << rec(1, 1, 1) << endl;
  }
}