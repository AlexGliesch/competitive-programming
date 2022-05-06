#include "includes.h"

class Solution {
public:
  bool hasPatternOfSize(int p, const string& s) {
    for (int i = 0; i < p; ++i) {
      int j = i + p;
      while (j < s.size()) {
        if (s[j] != s[i]) return false;
        j += p;
      }
    }
    return true;
  }

  bool repeatedSubstringPattern(string s) {
    int freq[26];
    fill(begin(freq), end(freq), 0);
    for (char c : s)
      ++freq[c - 'a'];
    int X = numeric_limits<int>::max();
    int n = s.size();
    for (int i : freq) {
      if (i > 0) {
        X = min(X, i);
      }
    }
    if (X == n) return n > 1; // only one type

    for (int j = 2; j <= X; ++j) {
      if (X % j == 0 && n % j == 0) {
        if (hasPatternOfSize(n / j, s)) return true;
      }
    }
    return false;
  }
};

// the letter that appears the least, let's say it appears X times
// then, the number of repetitions must be a divisor of X
// let's say  X = 2^a * 3^b * 5^c * 7^d * ...
// then, I'm trying at most a+b+c+d+... sizes
// at the worst case, when all letters have equal frequency and n is maximal and
// if X is a power of 2, X ~= 10^4 / 26 / 2 = 384 / 2 = 192 I can do 192 * 10^4
// = 1.920.000 operations
//
// 1. find X
// 2. if n % X != 0 return false;
// 3. for each divisor i of X, check whether I can make patterns of size i
//
// (in amortized cost, I can check for each j<X if X % j == 0. then j is a
// divisor)
//