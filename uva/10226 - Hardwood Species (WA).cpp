#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/* Não sei porque tá dando WA aqui. Não faz sentido. */

int main() {
  int t;
  cin >> t;
  string s;
  getline(cin, s);
  for (int i = 0; i < t; ++i) {
    double total = 0;
    if (i > 0)
      cout << endl;
    map<string, int> v;
    while (getline(cin, s), !s.empty()) {
      if (v.find(s) == v.end())
        v[s] = 1;
      else
        ++v[s];
      ++total;
    }
    for (map<string, int>::iterator i = v.begin(); i != v.end(); ++i) {
      cout << i->first << ' ' << setprecision(4) << fixed
           << 100.0 * (double)i->second / total << endl;
    }
  }
}