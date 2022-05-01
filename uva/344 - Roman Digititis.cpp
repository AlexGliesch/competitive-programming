#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* first get all roman numerals for 1..100, and count the letter
 * frequencies. then, accumulate them over 1..100.
 *
 * for each input, just print out the accumulated value.
 *
 * i found a nice function for converting an integer to roman numeral ;-)
 * credits to http://stackoverflow.com/a/19269226
 * */

string roman_numeral(int x) {
  static vector<pair<int, string>> numerals = {
      {100, "c"}, {90, "xc"}, {50, "l"}, {40, "xl"}, {10, "x"},
      {9, "ix"},  {5, "v"},   {4, "iv"}, {1, "i"}};

  string ans;
  for (const auto &num : numerals) {
    while (x >= num.first) {
      ans += num.second;
      x -= num.first;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  string characters = "ivxlc";
  vector<int> character_count[26];

  for (int i = 0; i <= 100; ++i) {
    string s = roman_numeral(i);
    for (auto c : characters) {
      int count = std::count(begin(s), end(s), c);
      character_count[c - 'a'].push_back(count);
    }
  }

  for (int i = 1; i <= 100; ++i) {
    for (auto c : characters)
      character_count[c - 'a'][i] += character_count[c - 'a'][i - 1];
  }

  int n;
  while (cin >> n, n) {
    cout << n << ":";
    for (auto c : characters) {
      cout << ' ' << character_count[c - 'a'][n] << ' ' << c;
      if (c != 'c')
        cout << ',';
    }
    cout << endl;
  }
}