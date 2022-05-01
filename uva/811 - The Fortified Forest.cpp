#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/* Convex hull, testing each possible solution: relatively simple.
 *
 * The big difficulty of the problem isn't the algorithm, but realizing that
 * you can't print an empty line after the last case, and you also can't print
 * a blank space after the list of cut trees. >:( */

struct Point {
  int x, y, v, l, i;
  bool operator<(const Point &p) const {
    return x < p.x or (x == p.x and y < p.y);
  }
};

int dist_sq(const Point &p1, const Point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/*  > 0 ccw
 *  < 0 cw
 *  = 0 collinear*/
int cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

double convex_hull(const vector<int> &p) {
  int n = p.size(), k = 0;
  vector<int> H(2 * n);

  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(P[H[k - 2]], P[H[k - 1]], P[p[i]]) <= 0)
      k--;
    H[k++] = p[i];
  }

  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && cross(P[H[k - 2]], P[H[k - 1]], P[p[i]]) <= 0)
      k--;
    H[k++] = p[i];
  }

  double perimeter = 0;
  for (int i = 0; i < k - 1; ++i)
    perimeter += sqrt(dist_sq(P[H[i]], P[H[i + 1]]));
  return perimeter;
}

int N;
vector<vector<int>> poss;
vector<int> poss_val;
vector<double> poss_extra;
vector<Point> P;
int total_len;
int total_val;

void rec(int i, const vector<int> &p, int len, int val) {
  if (i != N) {
    vector<int> p2(p);
    p2.erase(find(p2.begin(), p2.end(), i));

    double hull = convex_hull(p2);

    if (len + P[i].l >= hull) {
      poss.push_back(p2);
      poss_val.push_back(val + P[i].v);
      poss_extra.push_back((double)len + P[i].l - hull);
    } else {
      rec(i + 1, p2, len + P[i].l, val + P[i].v);
    }

    rec(i + 1, p, len, val);
  }
}

int main() {
  int t = 0, N;
  cout << setprecision(2) << fixed;

  while (cin >> N, N != 0) {
    P.clear();
    P.resize(N);
    poss.clear();
    poss_extra.clear();
    poss_val.clear();

    for (int i = 0; i < N; ++i) {
      cin >> P[i].x >> P[i].y >> P[i].v >> P[i].l;
      P[i].i = i + 1;
    }

    sort(P.begin(), P.end());

    total_len = 0;
    for (int i = 0; i < N; ++i)
      total_len += P[i].l;

    total_val = 0;
    for (int i = 0; i < N; ++i)
      total_val += P[i].v;

    vector<int> p(N);
    for (int i = 0; i < N; ++i)
      p[i] = i;
    rec(0, p, 0, 0);

    int best = 0;
    for (int i = 1; i < poss.size(); ++i) {
      if (poss_val[best] > poss_val[i] or
          (poss_val[best] == poss_val[i] and
           poss[i].size() >= poss[best].size())) {
        best = i;
      }
    }

    if (t != 0)
      cout << endl;

    cout << "Forest " << ++t << endl;
    cout << "Cut these trees:";

    set<int> cut;
    for (int i = 0; i < N; ++i) {
      if (find(poss[best].begin(), poss[best].end(), i) == poss[best].end()) {
        cut.insert(P[i].i);
      }
    }
    for (set<int>::iterator i = cut.begin(); i != cut.end(); ++i)
      cout << " " << *i;

    cout << endl;
    cout << "Extra wood: " << poss_extra[best] << endl;
  }
}