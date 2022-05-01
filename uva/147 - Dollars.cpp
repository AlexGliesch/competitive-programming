#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

int coins[] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
long long dp[6100][11];

long long coin_change(int amt, int c) {
  if (amt == 0)
    return 1;
  if (amt < 0 || c >= 11)
    return 0;
  if (dp[amt][c] != -1)
    return dp[amt][c];
  dp[amt][c] = coin_change(amt, c + 1) + coin_change(amt - coins[c], c);
  return dp[amt][c];
}

int main() {
  double x;
  memset(dp, -1, sizeof dp);
  while (cin >> x, x != 0.00) {
    cout << setprecision(2) << fixed << setw(6) << x << setw(17)
         << coin_change(x * 20, 0) << endl;
  }
}