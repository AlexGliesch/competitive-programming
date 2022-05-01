#include <cmath>
#include <iostream>

using namespace std;
using ll = long long;

/*
 * if 2^(b+1) is greater than n, then it's not possible, otherwise, it is
 * possible.
 *
 * an extra case is if b equals 0. in this case, for any n <= 1,
 * it is possible.
 * */

int main() {
  ll n, b;
  while (cin >> n >> b) {
    if (n <= 1 and b == 0)
      cout << "yes" << endl;
    else {
      ll x = pow(2, b + 1);
      if (n < x)
        cout << "yes" << endl;
      else
        cout << "no" << endl;
    }
  }
}
