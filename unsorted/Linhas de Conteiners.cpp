#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int l, c;
  while (cin >> l >> c) {
    vector<vector<int>> grid(l, vector<int>(c, 0));
    vector<vector<int>> gridT(c, vector<int>(l, 0));
    vector<int> line(c, 0);
    vector<int> column(l, 0);

    for (int i = 0; i < l; i++) {
      for (int j = 0; j < c; j++) {
        cin >> grid[i][j];
        gridT[j][i] = grid[i][j];

        if (i == 0) {
          line[j] = grid[i][j];
        }

        if (j == 0) {
          column[i] = grid[i][j];
        }
      }
    }

    int s = 0;

    int v = *min_element(line.begin(), line.end());
    for (int i = 0; i < c; i++) {
      if (line[i] != v) {
        for (int j = i + 1; j < c; j++) {
          if (line[j] == v) {
            int aux = line[i];
            line[i] = line[j];
            line[j] = aux;
            s++;
          }
        }
      }
      v++;
    }

    v = *min_element(column.begin(), column.end());

    for (int i = 0; i < l; i++) {
      if (column[i] != v) {
        for (int j = i + 1; j < l; j++) {
          if (column[j] == v) {
            int aux = column[i];
            column[i] = column[j];
            column[j] = aux;
            s++;
          }
        }
      }
      v += c;
    }

    /*for (int i = 0; i < l; i++) {
            cout << column[i] << endl;
    }*/

    bool correct = true;
    for (int i = 0; i < l; i++) {
      int v = *min_element(grid[i].begin(), grid[i].end());

      if ((v - 1) % c != 0) {
        // cout << "oi" << endl;
        correct = false;
        break;
      }

      for (int j = 0; j < c; j++) {
        if (grid[i][j] >= v + c) {
          correct = false;
          break;
        }
      }

      if (!correct) {
        break;
      }
    }

    if (correct) {
      for (int i = 0; i < c; i++) {
        int v = *min_element(gridT[i].begin(), gridT[i].end());
        int v_mod = v % c;

        if (v > c) {
          // cout << v << " " << c << endl;
          correct = false;
          break;
        }

        for (int j = 0; j < l; j++) {
          if (gridT[i][j] % c != v_mod) {
            correct = false;
            break;
          }
        }

        if (!correct) {
          break;
        }
      }
    }

    if (correct)
      cout << s << endl;
    else
      cout << "*" << endl;
  }
  return 0;
}