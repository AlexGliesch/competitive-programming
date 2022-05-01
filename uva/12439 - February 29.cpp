#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

/* A grande sacada está em encontrar uma fórmula O(1). A dica é:
* dados dois anos y1 e y2, o número de dias leap entre eles é todos os
* dias leap antes de y2 menos todos antes de y1. */

using namespace std;

map<string, int> month = {{"January", 1},  {"February", 2},  {"March", 3},
                          {"April", 4},    {"May", 5},       {"June", 6},
                          {"July", 7},     {"August", 8},    {"September", 9},
                          {"October", 10}, {"November", 11}, {"December", 12}};

tuple<int, int, int> read_date() {
  string mon;
  cin >> mon;
  int day, year;
  char dummy;
  cin >> day >> dummy >> year;
  return make_tuple(year, month[mon], day);
}

int leap_years(int y) { return y / 4 - y / 100 + y / 400; }

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    auto d1 = read_date();
    auto d2 = read_date();

    int y1 = get<0>(d1), y2 = get<0>(d2);

    if (d1 <= make_tuple(y1, 2, 29))
      --y1;
    if (d2 < make_tuple(y2, 2, 29))
      --y2;

    cout << "Case " << t << ": ";
    cout << leap_years(y2) - leap_years(y1) << endl;
  }
}