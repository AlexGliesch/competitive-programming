#include "includes.h"

class Solution {
public:
  int calculate(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    assert(find(s.begin(), s.end(), ' ') == s.end());
    vector<string> spl;
    size_t i = 0;
    while (true) {
      size_t j = s.find_first_of("+-*/", i);
      spl.emplace_back(s.begin() + i,
                       j == string::npos ? s.end() : s.begin() + j);
      if (j == string::npos) break;
      spl.emplace_back(string(1, s[j]));
      i = j + 1;
    }
    for (size_t i = 0; i < spl.size(); ++i) {
      if (spl[i] == "*" || spl[i] == "/") {
        int a = stoi(spl[i - 1]), b = stoi(spl[i + 1]);
        int r = spl[i] == "*" ? a * b : a / b;
        spl[i + 1] = to_string(r);
        spl[i].clear();
        spl[i - 1].clear();
        ++i;
      }
    }
    spl.erase(remove_if(spl.begin(), spl.end(),
                        [](const string& s) { return s.empty(); }),
              spl.end());

    int r = stoi(spl[0]);
    for (size_t i = 1; i < spl.size(); ++i) {
      if (spl[i] == "+" || spl[i] == "-") {
        int a = stoi(spl[i + 1]);
        if (spl[i] == "+")
          r += a;
        else
          r -= a;
        ++i;
      }
    }
    return r;
  }
};

int main() {
  Solution s;
  cout << s.calculate(" 7           *123/123+2-2-3+946 "
                      "*165/854-854+44/8-77+66* 99                       ")
       << endl;
}