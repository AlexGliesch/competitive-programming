#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;
  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++)
      P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
    }
  }

  vector<int> GetSuffixArray() {
    vector<int> res(L);
    for (int i=0; i<L; ++i)
      res[i] = M[i].second;
    return res;
  }

  vector<int> GetInvSuffixArray() { return P.back(); }

  // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
        i += 1 << k;
        j += 1 << k;
        len += 1 << k;
      }
    }
    return len;
  }
};

int main() {
  int n;
  string s, f;
  cin >> n >> s >> f;
  reverse(s.begin(), s.end());
  reverse(f.begin(), f.end());
  SuffixArray saObj(s);
  vector<int> sa = saObj.GetSuffixArray();
  vector<int> lcp;
  long long int best=0;
  for (int i=0, last=-1; i<n; ++i)
    if (f[sa[i]]=='0') {
      if (last != -1)
        lcp.push_back(saObj.LongestCommonPrefix(sa[last], sa[i]));
      best = max(best, n-(long long int)sa[i]);
      last = i;
    }
  vector<long long int> totalAmt(lcp.size(), 2);
  vector<pair<int, int> > st;
  for (int i=0; i<lcp.size(); ++i) {
    int amt=0;
    while (!st.empty() && st.back().first >= lcp[i]) {
      amt += st.back().second;
      st.pop_back();
    }
    st.push_back(make_pair(lcp[i], amt+1));
    totalAmt[i] += amt;
  }
  st.clear();
  for (int i=lcp.size()-1; i>=0; --i) {
    int amt=0;
    while (!st.empty() && st.back().first >= lcp[i]) {
      amt += st.back().second;
      st.pop_back();
    }
    st.push_back(make_pair(lcp[i], amt+1));
    totalAmt[i] += amt;
  }
  for (int i=0; i<lcp.size(); ++i)
    best = max(best, lcp[i]*totalAmt[i]);
  cout << best << endl;
}