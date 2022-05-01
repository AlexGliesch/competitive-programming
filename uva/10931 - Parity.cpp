#include <cstdint>
#include <iostream>

using namespace std;
using ll = int64_t;

int main() {
  ll x;
  while (cin >> x, x) {
    int parity = 0;
    cout << "The parity of ";
    for (int i = 63; i >= 0; --i) {
      if (x & (1LL << i)) {
        ++parity;
        cout << 1;
      } else if (parity)
        cout << 0;
    }
    cout << " is " << parity << " (mod 2).\n";
  }
}
