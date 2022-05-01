#include <iostream>
#include <string>

using namespace std;

int main() {
  string buf;
  getline(cin, buf);
  int cases = stoi(buf);
  for (int i = 0; i < cases; ++i) {
    string r, a, b;
    getline(cin, r);
    getline(cin, a);
    getline(cin, b);
    int av = 0, bv = 0;
    for (int i = 0; i < (int)r.size(); ++i) {
      av += r[i] == a[i];
      bv += r[i] == b[i];
    }
    cout << "Instancia " << i + 1 << endl;
    if (av > bv) cout << "time 1" << endl;
    else if (av == bv) cout << "empate" << endl;
    else cout << "time 2" << endl;
    cout << endl;
  }
}
