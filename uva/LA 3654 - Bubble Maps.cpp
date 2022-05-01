#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Just recursively manipulate the original string. */

/*--------------*
 |	p	|	q	|
 |--------------|
 |	s	|	r	|
 *--------------**/

string left(string s) {
  char c = s[s.size() - 1];
  s.erase(s.size() - 1, 1);
  if (c == 'm')
    s = "<none>";
  if (c == 's')
    s = left(s) + 'r';
  if (c == 'r')
    s = s + 's';
  if (c == 'p')
    s = left(s) + 'q';
  if (c == 'q')
    s = s + 'p';
  return (s[0] == '<') ? "<none>" : s;
}

string right(string s) {
  char c = s[s.size() - 1];
  s.erase(s.size() - 1, 1);
  if (c == 'm')
    s = "<none>";
  if (c == 's')
    s = s + 'r';
  if (c == 'r')
    s = right(s) + 's';
  if (c == 'p')
    s = s + 'q';
  if (c == 'q')
    s = right(s) + 'p';
  return (s[0] == '<') ? "<none>" : s;
}

string bottom(string s) {
  char c = s[s.size() - 1];
  s.erase(s.size() - 1, 1);
  if (c == 'm')
    s = "<none>";
  if (c == 's')
    s = bottom(s) + 'p';
  if (c == 'r')
    s = bottom(s) + 'q';
  if (c == 'p')
    s = s + 's';
  if (c == 'q')
    s = s + 'r';
  return (s[0] == '<') ? "<none>" : s;
}

string top(string s) {
  char c = s[s.size() - 1];
  s.erase(s.size() - 1, 1);
  if (c == 'm')
    s = "<none>";
  if (c == 's')
    s = s + 'p';
  if (c == 'r')
    s = s + 'q';
  if (c == 'p')
    s = top(s) + 's';
  if (c == 'q')
    s = top(s) + 'r';
  return (s[0] == '<') ? "<none>" : s;
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    string C;
    cin >> C;
    cout << top(C) << " " << bottom(C) << " " << left(C) << " " << right(C)
         << endl;
  }
}
