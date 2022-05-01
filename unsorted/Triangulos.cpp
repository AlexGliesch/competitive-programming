#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  int n;
  while (cin >> n) {
    vector<int> v(n);
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
      cin >> v[i];
      sum += v[i];
    }
    int ans = 0;
    if (sum % 3 != 0) {
      cout << 0 << endl;
    } else {
      ll arclen = sum / 3;
      int j = 0;
      int k = 0;
      int valj = 0;
      int valk = 0;
      int vali = 0;
      for (int i = 0; i < n; ++i) {
        while (valj < vali + arclen) {
          valj += v[j];
          j = (j + 1) % n;
        }
        if (valj == vali + arclen) {
          while (valk < vali + 2 * arclen) {
            valk += v[k];
            k = (k + 1) % n;
          }
          if (valk == vali + 2 * arclen) {
            ++ans;
          }
        }
        vali += v[i];
      }
      cout << ans / 3 << endl;
    }
  }
}
