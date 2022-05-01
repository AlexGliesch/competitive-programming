#include <array>
#include <iostream>

using namespace std;
using ll = long long;
using mat2 = array<array<ll, 2>, 2>;

/*
 * for a given number of years N, the number of female bees is fibonacci(N + 2)
 * - 1, and the number of male bees is fibonacci(N + 3) - 1.
 * */

mat2 mmult(mat2 &a, mat2 &b) {
  mat2 res;
  res[0][0] = (a[0][0] * b[0][0]) + (a[0][1] * b[1][0]);
  res[0][1] = (a[0][0] * b[0][1]) + (a[0][1] * b[1][1]);
  res[1][0] = (a[1][0] * b[0][0]) + (a[1][1] * b[1][0]);
  res[1][1] = (a[1][0] * b[0][1]) + (a[1][1] * b[1][1]);
  return move(res);
}

ll fib(int n) {
  mat2 ans = {{{1, 0}, {0, 1}}}, pow = {{{1, 1}, {1, 0}}};
  for (ll i = 0; i < 32; ++i) {
    if (n & (1 << i))
      ans = mmult(pow, ans);
    pow = mmult(pow, pow);
  }
  return ans[1][0];
}

int main() {
  int N;
  while (cin >> N, N != -1) {
    ll f = fib(N + 2);
    ll f1 = fib(N + 3);
    cout << f - 1 << ' ' << f1 - 1 << endl;
  }
}
