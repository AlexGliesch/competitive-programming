#include <algorithm>
#include <ciso646>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#define INF (1LL << 28LL)
#define MAX 510

using namespace std;
typedef long long ll;

/* 2D segment tree node */
struct Point {
  ll x, y, mx;
  Point() {}
  Point(ll x, ll y, ll mx) : x(x), y(y), mx(mx) {}
  bool operator<(const Point &other) const { return mx < other.mx; }
};

struct SegTree2D {
private:
  Point T[2 * MAX * MAX];
  ll n, m;

  Point build(ll node, ll a1, ll b1, ll a2, ll b2, ll P[MAX][MAX]) {
    if (a1 > a2 or b1 > b2)
      return def();

    if (a1 == a2 and b1 == b2)
      return T[node] = Point(a1, b1, P[a1][b1]);

    T[node] = def();
    T[node] = maxNode(
        T[node], build(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, P));
    T[node] = maxNode(T[node], build(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2,
                                     (b1 + b2) / 2, P));
    T[node] = maxNode(T[node], build(4 * node + 0, a1, (b1 + b2) / 2 + 1,
                                     (a1 + a2) / 2, b2, P));
    T[node] = maxNode(T[node], build(4 * node + 1, (a1 + a2) / 2 + 1,
                                     (b1 + b2) / 2 + 1, a2, b2, P));
    return T[node];
  }

  Point query(ll node, ll a1, ll b1, ll a2, ll b2, ll x1, ll y1, ll x2, ll y2) {
    if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2)
      return def();
    if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2)
      return T[node];
    Point mx = def();
    mx = maxNode(mx, query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2,
                           x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2,
                           (b1 + b2) / 2, x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2,
                           b2, x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1,
                           a2, b2, x1, y1, x2, y2));
    return mx;
  }

  Point update(ll node, ll a1, ll b1, ll a2, ll b2, ll x, ll y, ll value) {
    if (a1 > a2 or b1 > b2)
      return def();

    if (x > a2 or y > b2 or x < a1 or y < b1)
      return T[node];

    if (x == a1 and y == b1 and x == a2 and y == b2)
      return T[node] = Point(x, y, value);

    Point mx = def();
    mx = maxNode(mx, update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2,
                            x, y, value));
    mx = maxNode(mx, update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2,
                            (b1 + b2) / 2, x, y, value));
    mx = maxNode(mx, update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2,
                            b2, x, y, value));
    mx = maxNode(mx, update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1,
                            a2, b2, x, y, value));
    return T[node] = mx;
  }

public:
  /*
  * initialize and construct segment tree from grid of values P with size
  * n x m
  * */
  void init(ll n, ll m, ll P[MAX][MAX]) {
    this->n = n;
    this->m = m;
    build(1, 1, 1, n, m, P);
  }

  /* query from range [ (x1, y1), (x2, y2) ]
  * Time: O(logn) */
  Point query(ll x1, ll y1, ll x2, ll y2) {
    return query(1, 1, 1, n, m, x1, y1, x2, y2);
  }

  /* update the value of (x, y) index to 'value'
  * Time: O(logn) */
  Point update(ll x, ll y, ll value) {
    return update(1, 1, 1, n, m, x, y, value);
  }

  /* change this according to application: get the maximum, the minimum,
  * the sum, the product, etc. Don't foret to change def() */
  virtual Point maxNode(Point a, Point b) = 0;

  /* default node: change according to maxNode, for instance, if it's sum,
  * return 0, or if max, return -INF, or if min, +INF.*/
  virtual Point def() = 0;
};

struct MaxSegTree2D : public SegTree2D {
  Point maxNode(Point a, Point b) { return Point(0, 0, max(a.mx, b.mx)); }

  Point def() { return Point(0, 0, -INF); }
};

struct MinSegTree2D : public SegTree2D {
  Point maxNode(Point a, Point b) { return Point(0, 0, min(a.mx, b.mx)); }

  Point def() { return Point(0, 0, INF); }
};

ll N, P[MAX][MAX];
MinSegTree2D min_st;
MaxSegTree2D max_st;

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> N) {
    for (ll i = 1; i <= N; ++i)
      for (ll j = 1; j <= N; ++j)
        cin >> P[i][j];

    min_st.init(N + 1, N + 1, P);
    max_st.init(N + 1, N + 1, P);
    ;

    ll Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
      char c;
      cin >> c;
      if (c == 'c') {
        ll x, y, v;
        cin >> x >> y >> v;
        min_st.update(x, y, v);
        max_st.update(x, y, v);
      } else if (c == 'q') {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << max_st.query(x1, y1, x2, y2).mx << " "
             << min_st.query(x1, y1, x2, y2).mx << endl;
      }
    }
  }
}