#include <array>
#include <cstring>
#include <iostream>

using namespace std;
using ll = long long;
using mat2 = array<array<ll, 2>, 2>;

/*
 * must calculate fibonacci using O(log n) solution, with matrix
 * multiplications.
 *
 * for a given number n, for each bit of n with index #i that is 1, multiply
 * fib_m ^ i to the final result, where fib_m is the matrix
 * [[ 1, 1 ], [ 1, 0 ]]. the final result starts with the identity matrix.
 *
 * the final result is then ans[1][0] or ans[0][1]. see page 364 of the
 * programming challenges book (3rd edition).
 * */

mat2 mmult(mat2 &a, mat2 &b, ll mod) {
  mat2 res;
  res[0][0] = ((a[0][0] * b[0][0]) + (a[0][1] * b[1][0])) % mod;
  res[0][1] = ((a[0][0] * b[0][1]) + (a[0][1] * b[1][1])) % mod;
  res[1][0] = ((a[1][0] * b[0][0]) + (a[1][1] * b[1][0])) % mod;
  res[1][1] = ((a[1][0] * b[0][1]) + (a[1][1] * b[1][1])) % mod;
  return move(res);
}

int main() {
  ll m, n;
  while (cin >> n >> m) {
    if (n <= 1)
      cout << n << endl;
    else {
      ll mod = (1LL << m);
      mat2 ans = {{{1, 0}, {0, 1}}}, pow = {{{1, 1}, {1, 0}}};
      for (ll i = 0; i < 32; ++i) {
        if (n & (1 << i))
          ans = mmult(pow, ans, mod);
        pow = mmult(pow, pow, mod);
      }
      cout << ans[1][0] << endl;
    }
  }
}