#include <iostream>
#include <string>

using namespace std;

int dateToInt(int m, int d, int y) {
  return 1461 * (y + 4800 + (m - 14) / 12) / 4 +
         367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
         3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 + d - 32075;
}

int main() {
  string s;
  while (cin >> s) {
    string d, m, y;
    int i = 0;
    while (s[i] != '/')
      d.push_back(s[i++]);
    ++i;
    while (s[i] != '/')
      m.push_back(s[i++]);
    ++i;
    while (i < s.size())
      y.push_back(s[i++]);
    int today = dateToInt(11, 7, 2016),
        date = dateToInt(stoi(m), stoi(d), stoi(y));
    int diff = today - date;
    int x1 = diff % 23;
    int x2 = diff % 28;
    int x3 = diff % 33;
    if (x1 == 0)
      cout << "ZERADO ";
    else if (x1 > 11)
      cout << "NEGATIVO ";
    else
      cout << "POSITIVO ";

    if (x2 == 0 or x2 == 14)
      cout << "ZERADO ";
    else if (x2 > 14)
      cout << "NEGATIVO ";
    else
      cout << "POSITIVO ";

    if (x3 == 0)
      cout << "ZERADO\n";
    else if (x3 > 16)
      cout << "NEGATIVO\n";
    else
      cout << "POSITIVO\n";
  }
}
