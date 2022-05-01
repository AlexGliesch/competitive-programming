#include <algorithm>
#include <ciso646>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  int k, n;
  while (cin >> k >> n, k and n) {
    vector<vector<int>> rv(n);
    vector<string> name(n);
    vector<bool> problem(n, false);

    for (int i = 0; i < n; ++i) {
      cin >> name[i];
      for (int j = 0; j < k; ++j) {
        int x;
        cin >> x;
        --x;
        if (find(begin(rv[x]), end(rv[x]), i) != end(rv[x]))
          problem[x] = true;
        rv[x].push_back(i);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (rv[i].size() != k)
        problem[i] = true;
      else
        for (auto reviewer : rv[i]) {
          if (name[i] == name[reviewer])
            problem[i] = true;
          else if (reviewer == i)
            problem[i] = true;
        }
    }

    int num_problems =
        count_if(begin(problem), end(problem), [](bool b) { return b; });
    if (num_problems == 0)
      cout << "NO PROBLEMS FOUND" << endl;
    else if (num_problems == 1)
      cout << "1 PROBLEM FOUND" << endl;
    else
      cout << num_problems << " PROBLEMS FOUND" << endl;
  }
}