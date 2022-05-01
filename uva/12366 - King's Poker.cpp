#include <algorithm>
#include <ciso646>
#include <iostream>

using namespace std;

void check_pair(int p, int k) {
  if (k == 13) {
    cout << "1 " << p + 1 << ' ' << p + 1 << endl;
  } else {
    if (k + 1 == p) {
      if (k + 2 <= 13)
        cout << p << ' ' << p << ' ' << k + 2 << endl;
      else {
        if (p < 13)
          cout << "1 " << p + 1 << ' ' << p + 1 << endl;
        else
          cout << "1 1 1" << endl;
      }
    } else if (k + 1 < p)
      cout << k + 1 << ' ' << p << ' ' << p << endl;
    else
      cout << p << ' ' << p << ' ' << k + 1 << endl;
  }
}

int main() {
  int a, b, c;
  while (cin >> a >> b >> c, a != 0) {
    if (a == b and c != a) {
      check_pair(a, c);
    } else if (a == c and b != a) {
      check_pair(a, b);
    } else if (b == c and b != a) {
      check_pair(b, a);
    } else if (a == b and a == c) {
      if (a == 13 and b == 13 and c == 13)
        cout << '*' << endl;
      else
        cout << a + 1 << ' ' << a + 1 << ' ' << a + 1 << endl;
    } else {
      cout << "1 1 2" << endl;
    }
  }
}