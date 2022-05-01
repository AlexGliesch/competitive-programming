#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

typedef long long int lli;

int main() {
  int n, m;
  int ta=1;
  while (scanf("%d %d", &n, &m)==2) {
    printf("Case %d:\n", ta++);
    vector<int> color(n);
    for (int i=0; i<n; ++i)
      scanf("%d", &(color[i]));
    vector<vector<pair<int, lli> > > g(n);
    for (int i=0; i<m; ++i) {
      int u, v;
      lli w;
      scanf("%d %d %lld", &u, &v, &w);
      u--;
      v--;
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
    for (auto& v : g) {
      sort(v.begin(), v.end());
      vector<pair<int, lli> > nv;
      for (auto p : v)
        if (nv.empty() || p.first != nv.back().first)
          nv.push_back(p);
        else
          nv.back().second += p.second;
      v = nv;
    }
    vector<pair<int, int> > degList;
    for (int i=0; i<n; ++i)
      degList.emplace_back(g[i].size(), i);
    sort(degList.begin(), degList.end(), greater<pair<int, int> >());
    vector<bool> isHighDeg(n, false);
    for (int i=0; degList[i].first > i; ++i)
      isHighDeg[degList[i].second] = true;
    vector<vector<pair<int, lli> > > highDegG(n);
    vector<lli> sum(3, 0);
    vector<vector<lli> > highDegSum(n, vector<lli>(2, 0));
    for (int i=0; i<n; ++i)
      for (auto p : g[i]) {
        sum[color[i] + color[p.first]] += p.second;
        if (isHighDeg[p.first]) {
          highDegG[i].push_back(p);
          highDegSum[p.first][color[i]] += p.second;
        }
      }
    for (int i=0; i<3; ++i)
      sum[i] /= 2;
    int q;
    scanf("%d", &q);
    char s[] = "Asksum";
    for (int qa=0; qa<q; ++qa) {
      scanf("%s", s);
      if (s[0] == 'A') {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld\n", sum[a+b]);
      } else {
        int x;
        scanf("%d", &x);
        x--;
        for (auto p : highDegG[x]) {
          highDegSum[p.first][color[x]] -= p.second;
          highDegSum[p.first][1-color[x]] += p.second;
        }
        if (isHighDeg[x]) {
          for (int c=0; c<=1; ++c) {
            sum[color[x]+c] -= highDegSum[x][c];
            sum[1-color[x]+c] += highDegSum[x][c];
          }
        } else {
          for (auto p : g[x]) {
            sum[color[x]+color[p.first]] -= p.second;
            sum[1-color[x]+color[p.first]] += p.second;
          }
        }
        color[x] = 1-color[x];
      }
    }
  }
}