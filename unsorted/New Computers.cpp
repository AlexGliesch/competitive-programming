#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct point {
  double x, y;

  bool operator<(const point &p) const {
    return x < p.x or x == p.x and y < p.y;
  }

  bool operator==(const point &p) const { return x == p.x and y == p.y; }
};

/*  > 0 ccw, < 0 cw, =0 collinear*/
int cross(point p, point q, point r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

double d2d(point p, point q) {
  return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

vector<point> convex_hull(vector<point> p) {
  int n = p.size(), k = 0;
  vector<point> h(2 * n);
  sort(p.begin(), p.end());
  for (int i = 0; i < n; i++) {
    while (k >= 2 and cross(h[k - 2], h[k - 1], p[i]) < 0)
      k--;
    h[k++] = p[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t and cross(h[k - 2], h[k - 1], p[i]) < 0)
      k--;
    h[k++] = p[i];
  }
  h.resize(k);
  while (h[h.size() - 1] == h[0])
    h.pop_back();
  return h;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n, n) {
    vector<point> p(n);
    for (int i = 0; i < n; ++i)
      cin >> p[i].x >> p[i].y;
    cout << "Tera que comprar uma fita de tamanho ";
    p = convex_hull(p);
    if (p.size() < 3) {
      cout << "0.00";
    } else {
      double ans = d2d(p[0], p[p.size() - 1]);
      for (int i = 1; i < p.size(); ++i)
        ans += d2d(p[i], p[i - 1]);
      cout << setprecision(2) << fixed << ans;
    }
    cout << "." << endl;
  }
}