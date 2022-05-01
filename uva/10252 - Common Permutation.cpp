#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * count the frequencies of each letter in a and b. for each letter that appears
 * at least once in any of them, add to x the minimum number of times it appears
 * in any of them.
 *
 * sort x before printing it.
 *
 * important: input strings can be empty.
 * */

int main() {
  string a, b;
  while (getline(cin, a) and getline(cin, b)) {
    vector<int> ca(26, 0), cb(26, 0);
    for (auto c : a)
      ++ca[c - 'a'];
    for (auto c : b)
      ++cb[c - 'a'];

    string x;
    for (int i = 0; i < 26; ++i)
      for (int j = 0; j < min(ca[i], cb[i]); ++j)
        x.push_back(i + 'a');

    sort(begin(x), end(x));
    cout << x << endl;
  }
}