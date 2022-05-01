#include <algorithm>
#include <cctype>
#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * count the frequency for each letter and then sort the array. note: upper
 * case letters come before lower case in the ASCII table. ;)
 * */

int main() {
  string s;
  while (getline(cin, s)) {
    vector<pair<int, int>> freq(300);
    for (int i = 0; i < 300; ++i) {
      freq[i].first = i;
      freq[i].second = 0;
    }

    int max_freq = 0;
    for (auto i : s) {
      ++freq[i].second;
      if (isalpha(freq[i].first))
        max_freq = max(max_freq, freq[i].second);
    }

    sort(begin(freq), end(freq),
         [&](const pair<int, int> &a, const pair<int, int> &b) {
           if (a.second > b.second)
             return true;
           else if (a.second == b.second)
             return a.first < b.first;
           else
             return false;
         });

    for (int i = 0; i < 300; ++i) {
      if (freq[i].second == max_freq and isalpha(freq[i].first)) {
        cout << (char)freq[i].first;
      }
    }
    cout << " " << max_freq << endl;
  }
}
