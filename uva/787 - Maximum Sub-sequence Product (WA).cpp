#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

long long v[110], dp[110][110];

/* Tá dando WA por causa de integer overflow. Precisa usar BigInteger em
 * Java.*/

int main() {
  while (true) {
    int n = 0;
    long long res = -INT_MAX;

    while (cin >> v[n]) {
      if (v[n] == -999999)
        break;
      res = max(res, v[n]);
      ++n;
    }
    if (n == 0)
      break;

    for (int i = 0; i < n; ++i) {
      dp[i][i] = v[i];
      for (int j = i + 1; j < n; ++j) {
        dp[i][j] = v[j] * dp[i][j - 1];
        res = max(res, dp[i][j]);
      }
    }

    cout << res << endl;
  }
}