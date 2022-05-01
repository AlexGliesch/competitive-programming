#include <ciso646>
#include <iostream>

using namespace std;

int main() {
  int a, b, c;
  while (cin >> a >> b >> c) {
    if (a != b and b == c)
      cout << 'A' << endl;
    else if (b != c and a == c)
      cout << 'B' << endl;
    else if (c != a and a == b)
      cout << 'C' << endl;
    else
      cout << '*' << endl;
  }
}