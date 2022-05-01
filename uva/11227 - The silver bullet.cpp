#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#define eps 1e-9

using namespace std;

/* Teste de colinearidade. Via força bruta escolhe todos os pares de pontos,
 * e verifica quantos outros gnus estão na linha que liga o par de pontos.
 * Acha o máximo número de gnus.
 * Ps: pode ser feito com integer; para encontrar pontos únicos é mais rápido
 * std::set. */

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  bool operator<(const Point &p) const {
    return x < p.x or x == p.x and y < p.y;
  }
};

/*  > 0 ccw,  < 0 cw,  = 0 collinear */
int cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int N;
    cin >> N;
    set<Point> P_unique;
    vector<Point> P;
    for (int i = 0; i < N; ++i) {
      double x, y;
      cin >> x >> y;
      P_unique.emplace(int(x * 10000), int(y * 10000));
    }
    for (auto &p : P_unique) {
      P.emplace_back(move(p));
    }
    N = P.size();

    int ans = 0;
    if (N < 3)
      ans = N;
    else
      for (auto &i : P) {
        for (auto &j : P) {
          if (&j == &i)
            continue;
          int aligned = 2;
          for (auto &k : P) {
            if (&k == &i or &k == &j)
              continue;
            if (cross(i, j, k) == 0)
              ++aligned;
          }
          ans = max(ans, aligned);
        }
      }

    if (N == 1)
      cout << "Data set #" << t << " contains a single gnu." << endl;
    else
      cout << "Data set #" << t << " contains " << N
           << " gnus, "
              "out of which a maximum of "
           << ans << " are aligned." << endl;
  }
}