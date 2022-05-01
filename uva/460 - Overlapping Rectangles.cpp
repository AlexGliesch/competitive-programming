#include <algorithm>
#include <ciso646>
#include <iostream>

using namespace std;

/*
 * the overlap region is:
 * left = max(left1, left2)
 * right = min(right1, right2)
 * bottom = max(bottom1, bottom2)
 * top = min(top1, top2)
 *
 * if the overlap region creates a valid rectangle, then there is an overlap.
 * */

int main() {
  int left1, right1, top1, bottom1, left2, right2, top2, bottom2, ncases;
  cin >> ncases;
  for (int i = 0; i < ncases; ++i) {
    if (i)
      cout << endl;
    cin >> left1 >> bottom1 >> right1 >> top1;
    cin >> left2 >> bottom2 >> right2 >> top2;
    int left = max(left1, left2);
    int right = min(right1, right2);
    int bottom = max(bottom1, bottom2);
    int top = min(top1, top2);
    if (left < right and bottom < top)
      cout << left << " " << bottom << " " << right << " " << top << endl;
    else
      cout << "No Overlap" << endl;
  }
}