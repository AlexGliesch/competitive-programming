#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/* Count the number of students that are enrolled in a set of courses that
 * has maximum popularity. This can be done by adding the frequencies of
 * each set of courses. Tip: std::vector has operator< built-in! ;-)
 *
 * Important: there may be more than one set of courses
 * that is the most popular! */

int main() {
  int n;
  while (cin >> n, n) {
    map<vector<int>, int> m;
    int best = -1;
    for (int i = 0; i < n; ++i) {
      vector<int> v(5);
      for (auto &c : v)
        cin >> c;
      sort(v.begin(), v.end());
      best = max(best, ++m[v]);
    }
    int res = count_if(begin(m), end(m), [=](const decltype(m)::value_type &p) {
      return p.second == best;
    });
    cout << res * best << endl;
  }
}