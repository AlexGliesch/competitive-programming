#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

template <int D> struct KDNode {
  double x[D];
  int left = -1, right = -1;
};

template <int D> double DistSquared(double *a, double *b) {
  double d = 0;
  for (int i = 0; i < D; ++i)
    d += pow(a[i] - b[i], 2);
  return d;
}

template <int D> int Build(KDNode<D> *P, int from, int to, int dim) {
  if (from >= to)
    return -1;
  if (to == from + 1) {
    P[from].left = P[from].right = -1;
    return from;
  }
  int mid = (from + to) / 2;
  nth_element(P + from, P + mid, P + to,
              [&](KDNode<D> &a, KDNode<D> &b) { return a.x[dim] < b.x[dim]; });
  P[mid].left = Build(P, from, mid, (dim + 1) % D);
  P[mid].right = Build(P, mid + 1, to, (dim + 1) % D);
  return mid;
}

template <int D>
void Nearest(KDNode<D> *P, int idx, double *q, int dim, int &ans,
             double &ans_d) {
  if (idx == -1)
    return;
  auto &n = P[idx];

  double d = DistSquared<D>(n.x, q);
  if (d != 0 and (ans == -1 or d < ans_d))
    ans = idx, ans_d = d;

  double dx = q[dim] - n.x[dim];
  int s1 = n.left, s2 = n.right;
  if (dx > 0)
    swap(s1, s2);

  Nearest(P, s1, q, (dim + 1) % D, ans, ans_d);
  if (ans == -1 or dx * dx <= ans_d)
    Nearest(P, s2, q, (dim + 1) % D, ans, ans_d);
}

int main() {
  ios_base::sync_with_stdio(false);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<KDNode<2>> P(n);
    for (int i = 0; i < n; ++i)
      cin >> P[i].x[0] >> P[i].x[1];

    auto P2 = P;
    int root = Build(&P[0], 0, n, 0);

    for (auto &i : P2) {
      int ans = -1;
      double ans_d;
      Nearest(&P[0], root, i.x, 0, ans, ans_d);
      cout << fixed << (size_t)ans_d << endl;
    }

    //    Brute force approach O(n^2)
    //     for (int i = 0; i < (int)P2.size(); ++i) {
    //       double min_dist = -1;
    //       for (int j = 0; j < (int)P2.size(); ++j)
    //         if (i != j) {
    //           double d = DistSquared<2>(P2[i].x, P2[j].x);
    //           if (min_dist == -1 or d < min_dist)
    //             min_dist = d;
    //         }
    //       cout << fixed << (size_t)min_dist << endl;
    //     }
  }
}