#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Faz a recorrência, e guarda na dp quais os estados já visitados. Se um
 * estado já foi visitado, sai da recorrência. Para imprimir na ordem certa,
 * usei um vector<string> que depois imprime ao contrário, mas uma stack também
 * funciona. */

int Ca, Cb, n;
bool dp[1010][1010];
vector<string> s;

bool solve(int a, int b) {
  if (dp[a][b])
    return false;
  dp[a][b] = true;
  if (b == n)
    return true;

  if (a != Ca and solve(Ca, b)) {
    s.push_back("fill A");
    return true;
  } else if (b != Cb and solve(a, Cb)) {
    s.push_back("fill B");
    return true;
  } else if (a != 0 and solve(0, b)) {
    s.push_back("empty A");
    return true;
  } else if (b != 0 and solve(a, 0)) {
    s.push_back("empty B");
    return true;
  } else if (solve(max(0, a - (Cb - b)), min(Cb, a + b))) {
    s.push_back("pour A B");
    return true;
  } else if (solve(min(Ca, a + b), max(0, b - (Ca - a)))) {
    s.push_back("pour B A");
    return true;
  }
  return false;
}

int main() {
  while (cin >> Ca >> Cb >> n) {
    s.clear();
    memset(dp, false, sizeof dp);
    solve(0, 0);
    for (int i = s.size() - 1; i >= 0; --i)
      cout << s[i] << endl;
    cout << "success" << endl;
  }
}