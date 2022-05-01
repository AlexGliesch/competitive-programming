#include "includes.h"

class Solution {
public:
  bool buddyStrings(string s, string goal) {
    if (s.size() != goal.size()) return false;
    if (s == goal) {
      // if they're equal, only buddies if there are repeated characters
      vector<bool> num(255, false);
      for (size_t i = 0; i < s.size(); ++i)
        if (num[s[i]])
          return true;
        else
          num[s[i]] = true;
      return false;
    } else {
      // if they're not equal, only buddies if there are exactly 2 mismatches
      // and the character sets are the same
      int mis = 0;
      char mis1_s = 0, mis1_goal = 0;
      for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != goal[i]) {
          if (mis == 0) // first mismatch
            mis1_s = s[i], mis1_goal = goal[i];
          else if (s[i] != mis1_goal || goal[i] != mis1_s)
            return false;
          ++mis;
          if (mis > 2) return false;
        }
      return mis == 2;
    }
  }
};

int main() {
  Solution s;
  cout << s.buddyStrings("ab", "ba") << endl;
  cout << s.buddyStrings("ab", "ab") << endl;
  cout << s.buddyStrings("aa", "aa") << endl;
}