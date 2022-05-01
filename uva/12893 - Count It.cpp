#include <iostream>

using namespace std;

/* Just turn it in a recursive function, that way you can do it in log2(n) */

typedef unsigned long long ull;

ull func(ull n) {
  if (n == 0)
    return 0;
  return func(n / 2) + n % 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  ull T;
  cin >> T;
  while (T--) {
    ull n;
    cin >> n;
    cout << func(n) << endl;
  }
}
