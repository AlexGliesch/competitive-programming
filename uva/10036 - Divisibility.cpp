#include <cstring>
#include <iostream>

using namespace std;

/*
 * dp on (index, current_modulo).
 *
 * divisible(index, cur_mod, K):
 *		if index == N -> return MODULO(cur_mod, K) == 0
 *		else -> return divisible(index+1, MODULO(cur_mod + v[index], K))
 *OR
 *					   divisible(index+1, MODULO(cur_mod - v[index],
 *K));
 *
 * here, the modulo function must always return a positive value, so we can
 * easily DP it with an array 0-100.
 *
 * in order to do that, use MODULO(a, b) = ((a % b) + b) % b
 * (thanks to http://stackoverflow.com/a/12277233)
 *
 * */

int M, N, K, v[10010], dp[10010][110];

int modulo(int a, int b) { return ((a % b) + b) % b; }

bool divisible(int i, int mod) {
  if (i == N)
    return modulo(mod, K) == 0;
  if (dp[i][mod] != -1)
    return dp[i][mod];

  return dp[i][mod] = divisible(i + 1, modulo(mod - v[i], K)) ||
                      divisible(i + 1, modulo(mod + v[i], K));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> M;
  while (M--) {
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
      cin >> v[i];
    memset(dp, -1, sizeof dp);

    if (divisible(0, 0))
      cout << "Divisible" << endl;
    else
      cout << "Not divisible" << endl;
  }
}