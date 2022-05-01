#include "includes.h"

class Solution {
public:
  string getHint(string secret, string guess) {
    int bulls = 0, cows = 0;
    int unmatched_s[255], unmatched_g[255];
    fill(begin(unmatched_s), end(unmatched_s), 0);
    fill(begin(unmatched_g), end(unmatched_g), 0);
    for (size_t i = 0; i < secret.size(); ++i) {
      if (secret[i] == guess[i]) {
        ++bulls;
      } else {
        ++unmatched_s[secret[i]];
        ++unmatched_g[guess[i]];
      }
    }
    for (int i = 0; i < 255; ++i)
      cows += min(unmatched_g[i], unmatched_s[i]);

    stringstream ss;
    ss << bulls << "A" << cows << "B";
    return ss.str();
  }
};