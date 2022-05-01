#include <algorithm>
#include <ciso646>
#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << "Case " << i << ": ";
    if (a != min(a, min(b, c)) and a != max(a, max(b, c)))
      cout << a;
    if (b != min(a, min(b, c)) and b != max(a, max(b, c)))
      cout << b;
    if (c != min(a, min(b, c)) and c != max(a, max(b, c)))
      cout << c;
    cout << endl;
  }
}