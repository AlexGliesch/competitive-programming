#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, pair<pair<int, int>, vector<bool>>> ptype;
typedef pair<pair<int, int>, vector<bool>> ktype;

typedef pair<int, pair<pair<int, int>, vector<bool>>> teste;

int main() {
  int n;
  while (cin >> n) {
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      string str;
      cin >> str;
      for (int j = 0; j < n; j++) {
        char c = str[j];
        if (c >= 'a' && c <= 'j')
          mat[i][j] = c - 'a';
        else
          mat[i][j] = c - 'A' + 10;
      }
    }

    map<ktype, int> d;
    map<ktype, bool> v;

    priority_queue<ptype, vector<ptype>, greater<ptype>> q;

    vector<bool> pl(20, false);
    pl[(mat[0][0] + 10) % 20] = true;
    d[make_pair(make_pair(0, 0), pl)] = 1;
    q.push(make_pair(1, make_pair(make_pair(0, 0), pl)));

    bool np = true;
    while (!q.empty()) {
      int w = q.top().first;
      int x = q.top().second.first.first;
      int y = q.top().second.first.second;
      vector<bool> xl = q.top().second.second;
      q.pop();

      if (!v[make_pair(make_pair(x, y), xl)]) {
        v[make_pair(make_pair(x, y), xl)] = true;
        if (x == n - 1 && y == n - 1) {
          cout << w << endl;
          np = false;
          break;
        }
      }

      if (x - 1 >= 0) {
        vector<bool> xl2 = xl;
        xl2[(mat[x - 1][y] + 10) % 20] = true;
        if (!v[make_pair(make_pair(x - 1, y), xl2)] && !xl[mat[x - 1][y]]) {
          if (!d[make_pair(make_pair(x - 1, y), xl2)] ||
              d[make_pair(make_pair(x - 1, y), xl2)] >
                  d[make_pair(make_pair(x, y), xl)] + 1) {
            d[make_pair(make_pair(x - 1, y), xl2)] =
                d[make_pair(make_pair(x, y), xl)] + 1;
            q.push(make_pair(d[make_pair(make_pair(x - 1, y), xl2)],
                             make_pair(make_pair(x - 1, y), xl2)));
          }
        }
      }

      if (x + 1 <= n - 1) {
        vector<bool> xl2 = xl;
        xl2[(mat[x + 1][y] + 10) % 20] = true;
        if (!v[make_pair(make_pair(x + 1, y), xl2)] && !xl[mat[x + 1][y]]) {
          if (!d[make_pair(make_pair(x + 1, y), xl2)] ||
              d[make_pair(make_pair(x + 1, y), xl2)] >
                  d[make_pair(make_pair(x, y), xl)] + 1) {
            d[make_pair(make_pair(x + 1, y), xl2)] =
                d[make_pair(make_pair(x, y), xl)] + 1;
            q.push(make_pair(d[make_pair(make_pair(x + 1, y), xl2)],
                             make_pair(make_pair(x + 1, y), xl2)));
          }
        }
      }

      if (y - 1 >= 0) {
        vector<bool> xl2 = xl;
        xl2[(mat[x][y - 1] + 10) % 20] = true;
        if (!v[make_pair(make_pair(x, y - 1), xl2)] && !xl[mat[x][y - 1]]) {
          if (!d[make_pair(make_pair(x, y - 1), xl2)] ||
              d[make_pair(make_pair(x, y - 1), xl2)] >
                  d[make_pair(make_pair(x, y), xl)] + 1) {
            d[make_pair(make_pair(x, y - 1), xl2)] =
                d[make_pair(make_pair(x, y), xl)] + 1;
            q.push(make_pair(d[make_pair(make_pair(x, y - 1), xl2)],
                             make_pair(make_pair(x, y - 1), xl2)));
          }
        }
      }

      if (y + 1 <= n - 1) {
        vector<bool> xl2 = xl;
        xl2[(mat[x][y + 1] + 10) % 20] = true;
        if (!v[make_pair(make_pair(x, y + 1), xl2)] && !xl[mat[x][y + 1]]) {
          if (!d[make_pair(make_pair(x, y + 1), xl2)] ||
              d[make_pair(make_pair(x, y + 1), xl2)] >
                  d[make_pair(make_pair(x, y), xl)] + 1) {
            d[make_pair(make_pair(x, y + 1), xl2)] =
                d[make_pair(make_pair(x, y), xl)] + 1;
            q.push(make_pair(d[make_pair(make_pair(x, y + 1), xl2)],
                             make_pair(make_pair(x, y + 1), xl2)));
          }
        }
      }
    }

    if (np)
      cout << "-1" << endl;
  }
  return 0;
}