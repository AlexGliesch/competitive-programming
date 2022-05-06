#include "includes.h"

class Solution {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    // iterate over string i 0->size
    // keep num_distinct and update it dynamically
    // if see a new character c that would make num_distinct exceed k,
    //    while (num_distinct > k) increment left side

    if (k == 0) return k;
    int ans = 1;
    int left = 0, right = 1;
    int num_distinct = 1;
    int seen[255];
    fill(begin(seen), end(seen), 0);
    seen[s[0]] = 1;

    while (right < s.size()) {
      ++seen[s[right]];
      if (seen[s[right]] == 1) { // see new character
        ++num_distinct;
        while (num_distinct > k) {
          --seen[s[left]];
          if (seen[s[left]] == 0) --num_distinct;
          ++left;
        }
        assert(left <= right);
      } else {
        // character already seen, it's fine
      }
      ++right;
      ans = max(ans, right - left);
    }
    return ans;
  }
};