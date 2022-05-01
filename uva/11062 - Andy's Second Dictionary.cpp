#include <algorithm>
#include <ciso646>
#include <functional>
#include <iostream>
#include <set>
#include <string>

using namespace std;

/* my strategy:
 *
 * 1. put all lines in a same string. if a line ends with '-', pop
 * that character and append the end of the string to the start of the next
 * normally. if a line doesn't end with '-', append a space after the current
 * line.
 *
 * 2. transform all characters to lower case.
 *
 * 3. split the the big string using as delimiter any character that is not
 * alpha and not '-'.
 *
 * 4. add all elements to a set and print it.
 * */

void split_string(set<string> &output, const std::string &input,
                  const function<bool(char)> &pred, bool trim_empty = false) {
  auto it = begin(input);
  auto it_last = it;
  while (it = find_if(it, end(input), pred), it != end(input)) {
    if (not(trim_empty and it == it_last)) {
      output.emplace(it_last, it);
    }
    ++it;
    it_last = it;
  }
}

int main() {
  ios_base::sync_with_stdio(false);

  string text, s;
  while (getline(cin, s)) {
    if (s.back() == '-')
      s.pop_back();
    else
      s.push_back(' ');
    text += s;
  }

  transform(begin(text), end(text), begin(text),
            [](char c) { return std::tolower(c); });

  set<string> dictionary;
  split_string(dictionary, text,
               [](char c) { return not isalpha(c) and c != '-'; }, true);

  for (auto &s : dictionary)
    cout << s << endl;
}