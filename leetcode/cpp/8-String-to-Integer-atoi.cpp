#include "includes.h"

class Solution {
public:
  int myAtoi(string s) {
    string r;
    bool minus = false;
    size_t i = 0;
    while (s[i] == ' ')
      ++i;
    if (s[i] == '-')
      ++i, minus = true;
    else if (s[i] == '+')
      ++i;
    while (s[i] == '0')
      ++i;

    while (s[i] >= '0' && s[i] <= '9' && i < s.size())
      r.push_back(s[i]), ++i;

    if (r.empty()) return 0;

    bool clamp = false;
    if (r.size() < 10)
      clamp = false;
    else if (r.size() > 10)
      clamp = true;
    else {
      string two31 = minus ? "2147483648" : "2147483647";
      clamp = true;
      size_t i = 0;
      while (r[i] == two31[i] && i < 10)
        ++i;
      if (i <= 10) {
        clamp = r[i] > two31[i];
      }
    }

    if (clamp) {
      if (minus)
        return -(1LL << 31);
      else
        return (1LL << 31) - 1;
    } else {
      long long ans = 0, mul = 1;
      for (int i = (int)r.size() - 1; i >= 0; --i) {
        ans += mul * (r[i] - '0');
        mul *= 10;
      }
      assert(!minus && ans <= ((1LL << 31) - 1) || minus && ans <= (1LL << 31));
      return minus ? -ans : ans;
    }
  }
};