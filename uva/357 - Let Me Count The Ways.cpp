#include <cstring>
#include <iostream>

using namespace std;

int coins[] = {1, 5, 10, 25, 50};
long long dp[30100][5];

long long coin_change(int amt, int c) {
  if (amt == 0)
    return 1;
  if (amt < 0 || c >= 5)
    return 0;
  if (dp[amt][c] != -1)
    return dp[amt][c];
  dp[amt][c] = coin_change(amt, c + 1) + coin_change(amt - coins[c], c);
  return dp[amt][c];
}

int main() {
  int x;
  memset(dp, -1, sizeof dp);
  while (cin >> x) {
    long long y = coin_change(x, 0);
    if (y == 1) {
      cout << "There is only 1 way to produce " << x << " cents change."
           << endl;
    } else {
      cout << "There are " << y << " ways to produce " << x << " cents change."
           << endl;
    }
  }
}