#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Para cada query, vai para a direita e a esquerda e conta o número de casas
 * para cada lado até chegar num nome. Se L < R, printa right of..., se R < L,
 * printa left of..., se R == L printa middle */

int main() {
  int n;
  cin >> n;
  vector<string> v(n);
  for (int i = 0; i < n; ++i)
    cin >> v[i];
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int p;
    cin >> p;
    --p;
    if (v[p] != "?") {
      cout << v[p] << endl;
      continue;
    }
    int left, right;
    for (right = p + 1; right < n and v[right] == "?"; ++right)
      ;
    for (left = p - 1; left >= 0 and v[left] == "?"; --left)
      ;
    if ((left < 0 or right - p < p - left) and right < n) {
      for (int i = 0; i < right - p; ++i)
        cout << "left of ";
      cout << v[right] << endl;
    } else if ((right >= n or p - left < right - p) and left >= 0) {
      for (int i = 0; i < p - left; ++i)
        cout << "right of ";
      cout << v[left] << endl;
    } else if (p - left == right - p) {
      cout << "middle of " << v[left] << " and " << v[right] << endl;
    }
  }
}