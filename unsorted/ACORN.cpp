#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi trees;
vvi memo;
int f;

int dp(int t, int h) {
  if (h < 0)
    return 0;
  if (memo[t][h] > -1) {
    return memo[t][h];
  } else {
    int r = dp(t, h - 1);
    if (trees[t][h] > 0)
      for (int i = 0; i < trees.size(); i++)
        if (i != t)
          r = max(r, dp(i, h - f));

    return memo[t][h] = trees[t][h] + r;
  }
}

int main() {
  int c;
  cin >> c;
  while (c-- > 0) {
    int t, h;
    cin >> t >> h >> f;
    trees.assign(t, vi(h + 1, 0));
    memo.assign(t, vi(h + 1, -1));
    for (int i = 0; i < t; i++) {
      int s;
      cin >> s;
      for (int j = 0; j < s; j++) {
        int a;
        cin >> a;
        trees[i][a]++;
      }
    }
    int r = 0;
    for (int i = 0; i < t; i++)
      r = max(r, dp(i, h));
    cout << r << endl;
  }
}
