#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/* Usa dist�ncia euclideana. N�o esquecer de dar sort nos pontos, de acordo
 * com o eixo x. Para encontrar o y do in�cio de cada sol, pega o y do
 * �ltimo pico grande, que n�o seja maior que o atual. O x consegui via
 * semelhan�a de tri�ngulos. */

struct Point {
  double x, y;
  bool operator<(const Point &p) const { return x < p.x; }
} pt[105];

double dist(const Point &p1, const Point &p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
  int c;
  cin >> c;
  cout << setprecision(2) << fixed;

  while (c--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> pt[i].x >> pt[i].y;
    sort(pt, pt + n);

    double ans = 0;
    for (int i = n - 1; i >= 1;) {
      ans += dist(pt[i], pt[i - 1]);
      int j = i - 1;
      while (j >= 0 and pt[j].y <= pt[i - 1].y)
        --j;
      if (j < 0)
        break;
      double dxdy = (pt[j + 1].x - pt[j].x) / (pt[j].y - pt[j + 1].y);
      pt[j + 1].x -= dxdy * (pt[i - 1].y - pt[j + 1].y);
      pt[j + 1].y = pt[i - 1].y;
      i = j + 1;
    }
    cout << ans << endl;
  }
}
