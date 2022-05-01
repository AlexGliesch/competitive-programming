#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/* Classic convex hull. Find the perimeter of each hull. */

struct Point {
  double x, y;
  bool operator<(const Point &p) const {
    return x < p.x or (x == p.x and y < p.y);
  }
};

ostream &operator<<(ostream &os, const Point &p) {
  cout << setprecision(1) << fixed;
  cout << "(" << p.x << "," << p.y << ")";
  return os;
}

double dist(const Point &p1, const Point &p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/*  > 0 ccw
 *  < 0 cw
 *  = 0 collinear*/
double cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

vector<Point> convex_hull(vector<Point> P) {
  int n = P.size(), k = 0;
  vector<Point> H(2 * n);

  sort(P.begin(), P.end());

  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }

  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }

  H.resize(k);
  return H;
}

int main() {
  int t = 0, N;
  while (cin >> N, N != 0) {
    vector<Point> P(N);
    for (int i = 0; i < N; ++i)
      cin >> P[i].x >> P[i].y;

    vector<Point> hull = convex_hull(P);

    cout << "Region #" << ++t << ":" << endl;
    double perimeter = 0.0;
    for (int i = hull.size() - 1; i > 0; --i) {
      perimeter += dist(hull[i], hull[i - 1]);
      cout << hull[i] << "-";
    }
    cout << hull[0] << endl;
    cout << "Perimeter length = " << setprecision(2) << fixed << perimeter
         << endl;
    cout << endl;
  }
}