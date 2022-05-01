#include <ciso646>
#include <iostream>

using namespace std;

int main() {
  int t, total = 0;
  cin >> t;
  while (t--) {
    double len, wid, dep, we;
    cin >> len >> wid >> dep >> we;
    if (((len <= 56 and wid <= 45 and dep <= 25) or len + wid + dep <= 125) and
        we <= 7) {
      cout << 1 << endl;
      ++total;
    } else {
      cout << 0 << endl;
    }
  } /* Tem que printar endl no fim senão dá WA! */
  cout << total << endl;
}