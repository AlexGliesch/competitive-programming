#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int m, n;
  while (cin >> m >> n) {
    vector<vector<int>> plans(m, vector<int>(4, 0));
    for (int i = 0; i < m; i++) {
      cin >> plans[i][0] >> plans[i][1] >> plans[i][2] >> plans[i][3];
    }

    map<vector<int>, int> mapper;
    for (int i = 0; i < n; i++) {
      int x, y, z;
      cin >> x >> y >> z;

      vector<int> checker(m, 0);
      for (int j = 0; j < m; j++) {
        if (plans[j][0] * x + plans[j][1] * y + plans[j][2] * z - plans[j][3] >
            0) {
          checker[j] = 1;
        }
      }

      if (mapper[checker]) {
        mapper[checker] = mapper[checker] + 1;
      } else {
        mapper[checker] = 1;
      }
    }

    int max_size = 0;
    for (map<vector<int>, int>::iterator it = mapper.begin();
         it != mapper.end(); it++) {
      max_size = max(max_size, it->second);
    }

    cout << max_size << endl;
  }
  return 0;
}