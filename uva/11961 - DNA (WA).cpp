#include <algorithm>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int T, N, K;
set<string> mut;
string s;

void backtrack(int i, int k, const string &c) {
  if (i == N) {
    if (k == K)
      mut.insert(c);
    return;
  }

  backtrack(i + 1, k, c + s[i]);
  if (k < K) {
    backtrack(i + 1, k + 1, c + 'A');
    backtrack(i + 1, k + 1, c + 'C');
    backtrack(i + 1, k + 1, c + 'G');
    backtrack(i + 1, k + 1, c + 'T');
  }
}

int main() {
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N >> K >> s;
    backtrack(0, 0, string());
    cout << mut.size() << endl;
    for (set<string>::iterator i = mut.begin(); i != mut.end(); ++i)
      cout << *i << endl;
  }
}