#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#define PI 3.14159265358979323846

using namespace std;

struct point {
  double x, y;
};

double cross(point a, point b, point c) {
  return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

double area(point a, point b, point c) { return abs(cross(a, b, c)) / 2.0; }

bool point_in_triangle(point p, point a, point b, point c) {
  // Test if a point is inside a triangle. Adapted from
  // https://stackoverflow.com/a/2049593
  bool b1 = cross(p, a, b) < 0.0;
  bool b2 = cross(p, b, c) < 0.0;
  bool b3 = cross(p, c, a) < 0.0;
  return b1 == b2 and b2 == b3;
}

int v;
double dp[51][51];
point p[51];

// Find the triangulation with the largest triangle, on the subset polygon to
// the left of line defined by points l-r in the original polygon.
double solve(int a, int b) {
  auto& ans = dp[a][b];
  if (ans != -1.0) return ans;
  if (b == a + 1) return ans = 0;
  ans = DBL_MAX;
  for (int c = a + 1; c < b; ++c) {
    // Check if there are any points inside triangle acb. If yes, then this
    // triangle is not feasible, since it would go outside the polygon.
    bool ok = true;
    for (int i = 0; i < v; ++i)
      if (i != a and i != c and i != b)
        ok = ok and not point_in_triangle(p[i], p[a], p[c], p[b]);
    if (ok) {
      // Ok: solve the two created sub-problems (left of a-c, left of c-b) and
      // see which has a better triangulation
      double best = max(area(p[a], p[c], p[b]), max(solve(a, c), solve(c, b)));
      ans = min(ans, best);
    }
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    cin >> v;
    for (int i = 0; i < v; ++i)
      cin >> p[i].x >> p[i].y;
    for (auto& i : dp)
      for (auto& j : i)
        j = -1.0;
    cout << setprecision(1) << fixed << solve(0, v - 1) << endl;
  }
}
