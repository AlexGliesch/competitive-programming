#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int m[110][110], n, s, dp[110][110];

int rec(int i, int j) {
  if (m[i][j])
    return 0;
  if (dp[i][j] == -1) {
    int diag = rec(i + 1, j + 1);
    int up = rec(i + 1, j);
    int left = rec(i, j + 1);
    if (diag == 0) {
      dp[i][j] = 1 + max(left, up);
    } else {
      dp[i][j] = 1 + left + up - diag;
    }
  }
  return dp[i][j];
}

int main() {
  int ncases;
  cin >> ncases;
  for (int t = 0; t < ncases; ++t) {
    cin >> s >> n;

    memset(m, 0, sizeof m);
    for (int i = 0; i < n; ++i) {
      int r1, c1, r2, c2;
      cin >> r1 >> c1 >> r2 >> c2;
      for (int i = r1 - 1; i <= r2 - 1; ++i)
        for (int j = c1 - 1; j <= c2 - 1; ++j)
          m[i][j] = 1;
    }

    // for (int i=s-1;i>=0;--i) {
    //	for (int j=s-1;j>=0; --j) {
    //		if (m[i][j]) cout << "x" << " ";
    //		else cout << "- ";
    //	}
    //	cout << endl;
    //}
    // cout << endl;

    memset(dp, -1, sizeof dp);
    int ans = -1;
    for (int i = s - 1; i >= 0; --i) {
      for (int j = s - 1; j >= 0; --j) {
        ans = max(ans, rec(i, j));
      }
    }

    // for (int i=s-1;i>=0;--i) {
    //	for (int j=s-1;j>=0; --j) {
    //		cout << setw(2) << fixed << rec(i, j) << " ";
    //	}
    //	cout << endl;
    //}
    // cout << endl;

    cout << ans << endl;
  }
}
