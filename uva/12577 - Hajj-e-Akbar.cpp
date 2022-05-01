#include <iostream>
#include <string>

/* É só um if */

using namespace std;

int main() {
  string s;
  int i = 0;
  while (cin >> s, s != "*") {
    cout << "Case " << ++i << ": ";
    if (s[0] == 'H')
      cout << "Hajj-e-Akbar" << endl;
    else
      cout << "Hajj-e-Asghar" << endl;
  }
}