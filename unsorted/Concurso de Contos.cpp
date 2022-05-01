#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, L, C;

int main() {
  while (cin >> N >> L >> C) {
    int pages = 1;
    int chars_this_line = 0;
    int lines_this_page = 0;

    vector<string> v;
    for (int i = 0; i < N; ++i) {
      string s;
      cin >> s;
      v.push_back(s);
    }

    for (int i = 0; i < (int)v.size(); ++i) {
      chars_this_line += v[i].size();
      if (chars_this_line > C) {
        chars_this_line = v[i].size();
        ++lines_this_page;
        if (lines_this_page >= L) {
          lines_this_page = 0;
          ++pages;
        }
      }
      if (chars_this_line != 0 and chars_this_line + 1 <= C)
        ++chars_this_line;
    }

    cout << pages << endl;
  }
}