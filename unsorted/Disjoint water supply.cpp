#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> mi;

int main() {
  int c, p;
  while (cin >> c >> p) {
    mi mat(c + 1, vi());
    for (int i = 0; i < p; i++) {
      int a, b;
      cin >> a >> b;
      mat[b].push_back(a);
    }

    vi parents(c + 1, 0);
    parents[1] = 1;
    for (int i = 2; i <= c; i++) {
      parents[i] = parents[mat[i][0]];
      for (int j = 0; j < mat[i].size(); j++) {
        if (parents[mat[i][j]] != parents[mat[i][0]] || mat[i][j] == 1) {
          parents[i] = i;
          break;
        }
      }
    }

    int r = 0;
    for (int i = 1; i <= c; i++)
      for (int j = i + 1; j <= c; j++)
        if (parents[i] != parents[j]) {
          r++;
        }

    cout << r << endl;
  }
  return 0;
}