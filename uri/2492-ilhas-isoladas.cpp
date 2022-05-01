#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n == 0) break;
    set<string> in, out;
    string i, o, d;
    for (int j = 0; j < n; ++j) {
      cin >> i >> d >> o;
      in.insert(i);
      out.insert(o);
    }
    if (in.size() != n)
      cout << "Not a function.\n";
    else if (out.size() != n)
      cout << "Not invertible.\n";
    else
      cout << "Invertible.\n";
  }
}
