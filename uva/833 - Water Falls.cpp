#include <array>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/* Recursivamente vai caindo. É bom achar uma maneira fácil de determinar
 * qual o ponto da esquerda/direita num segmento. O segmento que ele cai em
 * cima é aquele que [left < x < right], e que tem a menor distância do y
 * até a intersecção com o segmento. Para encontrar a intersecção, acha a
 * equação da reta e substitui. O novo x vai depender se o y da esquerda é
 * maior ou menor que o da direita. Também dá pra calcular com o m da reta. */

struct Point {
  int x, y;
};
vector<array<Point, 2>> seg;
int NP, NS;

Point fall(Point p) {
  if (p.y == 0)
    return p;
  int closest = -1;
  double dist = numeric_limits<double>::max();
  for (int i = 0; i < NP; ++i) {
    if (p.x > seg[i][0].x and p.x < seg[i][1].x) {
      double m =
          (seg[i][0].y - seg[i][1].y) / double(seg[i][0].x - seg[i][1].x);
      double y = p.x * m + seg[i][0].y - m * seg[i][0].x;
      if (y < p.y and p.y - y < dist) {
        closest = i;
        dist = p.y - y;
      }
    }
  }
  if (closest == -1)
    return {p.x, 0};
  else if (seg[closest][0].y < seg[closest][1].y) {
    return fall(seg[closest][0]);
  } else {
    return fall(seg[closest][1]);
  }
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;
    cin >> NP;
    seg.resize(NP);
    for (int i = 0; i < NP; ++i) {
      cin >> seg[i][0].x >> seg[i][0].y >> seg[i][1].x >> seg[i][1].y;
      if (seg[i][0].x > seg[i][1].x)
        swap(seg[i][0], seg[i][1]);
    }

    cin >> NS;
    for (int i = 0; i < NS; ++i) {
      int x, y;
      cin >> x >> y;
      cout << fall({x, y}).x << endl;
    }
  }
}