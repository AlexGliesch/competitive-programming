#include <iostream>

using namespace std;

/* O resultado é n^2 + (n-1)^2 + (n-2)^2 + ... + 2^2 + 1^1
 * Dá pra guardar os 100 valores numa dp antes de começar a ler os inputs.
 * */

int main() {
  long long n, dp[101];
  dp[0] = 0;
  for (int i = 1; i <= 100; ++i) {
    dp[i] = dp[i - 1] + i * i;
  }
  while (cin >> n, n) {
    cout << dp[n] << endl;
  }
}