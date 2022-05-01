#include <algorithm>
#include <iostream>

using namespace std;

/* O problema está tagueado como DP, mas resolvi sem DP, em O(t). Como só há
 * 2 hamburgueres que ele pode comer, basta encontrar um ponto de corte entre
 * 1 e t, em que ele pára de comer um e começa a comer outro.
 *
 * Não esquecer que se sobrar minutos dos dois, ele ainda pode talvez
 * comer mais um.
*/

int main() {
  int m, n, t;
  while (cin >> m >> n >> t) {
    int beers = (1 << 28), burguers = 0;
    for (int i = 1; i <= t; ++i) {
      int ate = ((t - i) / m) + i / n, time_left = ((t - i) % m) + i % n;

      int drank = time_left;
      if (time_left >= n)
        drank = min(time_left - n, drank);
      if (time_left >= m)
        drank = min(time_left - m, drank);
      if (drank != time_left)
        ++ate;

      if (drank < beers || drank == beers && ate > burguers) {
        burguers = ate, beers = drank;
      }
    }
    cout << burguers;
    if (beers)
      cout << ' ' << beers;
    cout << endl;
  }
}