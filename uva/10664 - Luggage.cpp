#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* Easy problem, with low limits. Interestingly, the brute force solution
 * was faster than DP. */

int m, n, w[30], total_w;
int dp[30][250];

int rec(int i, int cur_w) {
  if (i == n)
    return cur_w == total_w / 2;
  if (dp[i][cur_w] != -1)
    return dp[i][cur_w];
  return dp[i][cur_w] = rec(i + 1, cur_w) + rec(i + 1, cur_w + w[i]);
}

int main() {
  string s;
  getline(cin, s);
  istringstream ss(s);
  ss >> m;
  for (int t = 0; t < m; ++t) {
    memset(dp, -1, sizeof dp);
    n = total_w = 0;
    getline(cin, s);
    istringstream ss(s);
    while (ss >> w[n]) {
      total_w += w[n];
      ++n;
    }
    cout << (total_w % 2 == 0 && rec(0, 0) ? "YES" : "NO") << endl;
  }
}