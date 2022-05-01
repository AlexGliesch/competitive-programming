#include <ciso646>
#include <iostream>

using namespace std;

/*
 * three lengths a, b and c make a triangle iff:
 * a + b > c AND
 * a + c > b AND
 * b + c > a
 *
 * USE LONG LONG
 * */

int main() {
  long long ncases, a, b, c;
  cin >> ncases;
  for (int i = 0; i < ncases; ++i) {
    cin >> a >> b >> c;
    cout << "Case " << i + 1 << ": ";
    if (a + b <= c or a + c <= b or b + c <= a or a <= 0 or b <= 0 or c <= 0) {
      cout << "Invalid" << endl;
    } else if (a == b and b == c) {
      cout << "Equilateral" << endl;
    } else if (a == b or a == c or b == c) {
      cout << "Isosceles" << endl;
    } else {
      cout << "Scalene" << endl;
    }
  }
}