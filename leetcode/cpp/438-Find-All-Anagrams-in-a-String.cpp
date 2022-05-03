#include "includes.h"

class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    if (p.size() > s.size()) return {};
    array<int, 26> pfreq, sfreq;
    fill(begin(sfreq), end(sfreq), 0);
    fill(begin(pfreq), end(pfreq), 0);
    for (char c : p)
      pfreq[c - 'a']++;

    // "cbaebabacd"
    // "abc"

    int i = 0, j = 0;
    while (j < p.size()) {
      sfreq[s[j] - 'a']++;
      ++j;
    }
    vector<int> ans;
    while (j < s.size()) {
      if (sfreq == pfreq) ans.push_back(i);
      sfreq[s[j] - 'a']++;
      sfreq[s[i] - 'a']--;
      ++i, ++j;
    }
    if (sfreq == pfreq) ans.push_back(i);
    return ans;
  }
};