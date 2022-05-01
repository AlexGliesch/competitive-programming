#include <ciso646>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int R, C, dp[105][105];
string buf;

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;
    cin >> R >> C;
    memset(dp, 0, sizeof dp);

    getline(cin, buf);
    for (int i = 0; i < R; ++i) {
      getline(cin, buf);
      istringstream ss(buf);
      int r, c;
      ss >> r;
      --r;
      while (ss >> c) {
        dp[r][c - 1] = -1;
      }
    }

    dp[0][0] = 1;
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if (dp[r][c] == -1)
          continue;
        if (r and dp[r - 1][c] != -1)
          dp[r][c] += dp[r - 1][c];
        if (c and dp[r][c - 1] != -1)
          dp[r][c] += dp[r][c - 1];
      }
    }
    cout << dp[R - 1][C - 1] << endl;
  }
}