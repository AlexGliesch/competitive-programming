#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int n, m;
vector<int> in, out;
map<vector<int>, bool> memo;
int maxout = 0;

vector<int> dobra(const vector<int> &v, int onde) {
  // onde=0 ou =n: não faz nada
  // onde=1: sobrepõe 1 com 2
  // onde=n-1: sobrepõe n-1 com n-2
  if (onde <= 0 or onde >= v.size())
    return v;

  vector<int> v2;
  int i = onde, j = onde - 1;
  for (; i < v.size() or j >= 0; ++i, --j) {
    int val = 0;
    if (i >= 0 and i < v.size())
      val += v[i];
    if (j >= 0 and j < v.size())
      val += v[j];
    v2.push_back(val);
  }
  assert(v2.size() <= v.size());
  /*cout << "dobra ";
  for (auto i:v)cout<< i<<" ";
  cout << " em " <<onde<< " = ";
  for (auto i:v2)cout<<i<<" ";
  cout<<endl;*/
  return move(v2);
}

bool pode(const vector<int> &v) {
  if (memo.find(v) != memo.end())
    return memo[v];
  if (v.size() < out.size())
    return memo[v] = false;
  if (v.size() == out.size()) {
    auto v2 = v;
    reverse(v2.begin(), v2.end());
    return memo[v] = (v == out or v2 == out);
  }

  for (int i = 0; i < v.size(); ++i) {
    if (v[i] > maxout)
      return memo[v] = false;
  }

  for (int i = 1; i < v.size(); ++i) {
    auto v2 = dobra(v, i);
    if (pode(v2))
      return memo[v] = true;
  }
  return memo[v] = false;
}

int main() {
  while (cin >> n) {
    int sumin = 0, sumout = 0;
    memo.clear();
    in.clear();
    in.resize(n);
    for (int i = 0; i < n; ++i) {
      cin >> in[i];
      sumin += in[i];
    }
    cin >> m;

    out.clear();
    out.resize(m);
    for (int i = 0; i < m; ++i) {
      cin >> out[i];
      sumout += out[i];
    }

    if (sumin != sumout) {
      cout << "N" << endl;
      continue;
    }
    maxout = 0;
    for (int i = 0; i < out.size(); ++i)
      maxout = max(maxout, out[i]);

    if (pode(in)) {
      cout << "S" << endl;
    } else {
      cout << "N" << endl;
    }
  }
}
