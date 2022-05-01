#include <iostream>
#include <string>

using namespace std;

/* always place the new container on top of the first stack it finds which
 * compares less or equal than its label. note that since we only care about
 * the top of the stack, we don't need to bother actually using std::stacks. */

int main() {
  int ncase = 0;
  string buf, s;
  while (getline(cin, buf), buf != "end") {
    s.clear();
    for (auto &i : buf) {
      for (auto &j : s) {
        if (i <= j) {
          j = i;
          goto leave;
        }
      }
      s.push_back(i);
    leave:;
    }
    cout << "Case " << ++ncase << ": " << s.size() << endl;
  }
}