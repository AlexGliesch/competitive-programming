#include "includes.h"

class Solution {
public:
  void rec(int n, int open, int closed, string& s, vector<string>& ans) {
    if (s.size() == n * 2)
      ans.push_back(s);
    else {
      if (open < n) {
        s.push_back('(');
        rec(n, open + 1, closed, s, ans);
        s.pop_back();
      }
      if (closed < open) {
        s.push_back(')');
        rec(n, open, closed + 1, s, ans);
        s.pop_back();
      }
    }
  }

  vector<string> generateParenthesis(int n) {
    string s;
    vector<string> ans;
    rec(n, 0, 0, s, ans);
    return ans;
  }
};

int main() {
  Solution s;
  auto v = s.generateParenthesis(1);
  for (auto i : v)
    cout << i << endl;
}