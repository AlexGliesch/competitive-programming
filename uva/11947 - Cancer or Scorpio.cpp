#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/*
        Used Stanford's dateToInt / intToDate conversion functions. Convert
   input
        date to int, add 40*7 to that, and convert back to date.

        In order to get the zodiac, store min and max dates for each zodiac,
   with
        year = 0. Convert the final date to year 0 (but same month and day) and
        check if it is between min and max for each zodiac. Default:
   "capricorn".
*/

/* converts Gregorian date to integer (Julian day number) */
int dateToInt(int m, int d, int y) {
  return 1461 * (y + 4800 + (m - 14) / 12) / 4 +
         367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
         3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 + d - 32075;
}

/* converts integer (Julian day number) to Gregorian date: month/day/year */
void intToDate(int jd, int &m, int &d, int &y) {
  int x, n, i, j;
  x = jd + 68569;
  n = 4 * x / 146097;
  x -= (146097 * n + 3) / 4;
  i = (4000 * (x + 1)) / 1461001;
  x -= 1461 * i / 4 - 31;
  j = 80 * x / 2447;
  d = x - 2447 * j / 80;
  x = j / 11;
  m = j + 2 - 12 * x;
  y = 100 * (n - 49) + i + x;
}

vector<string> zodiacs;
vector<int> min_zodiac, max_zodiac;

void populate() {
  zodiacs.push_back("aquarius");
  zodiacs.push_back("pisces");
  zodiacs.push_back("aries");
  zodiacs.push_back("taurus");
  zodiacs.push_back("gemini");
  zodiacs.push_back("cancer");
  zodiacs.push_back("leo");
  zodiacs.push_back("virgo");
  zodiacs.push_back("libra");
  zodiacs.push_back("scorpio");
  zodiacs.push_back("sagittarius");
  zodiacs.push_back("capricorn");

  min_zodiac.push_back(dateToInt(1, 21, 0));
  min_zodiac.push_back(dateToInt(2, 20, 0));
  min_zodiac.push_back(dateToInt(3, 21, 0));
  min_zodiac.push_back(dateToInt(4, 21, 0));
  min_zodiac.push_back(dateToInt(5, 22, 0));
  min_zodiac.push_back(dateToInt(6, 22, 0));
  min_zodiac.push_back(dateToInt(7, 23, 0));
  min_zodiac.push_back(dateToInt(8, 22, 0));
  min_zodiac.push_back(dateToInt(9, 24, 0));
  min_zodiac.push_back(dateToInt(10, 24, 0));
  min_zodiac.push_back(dateToInt(11, 23, 0));
  min_zodiac.push_back(dateToInt(12, 23, 0));

  max_zodiac.push_back(dateToInt(2, 19, 0));
  max_zodiac.push_back(dateToInt(3, 20, 0));
  max_zodiac.push_back(dateToInt(4, 20, 0));
  max_zodiac.push_back(dateToInt(5, 21, 0));
  max_zodiac.push_back(dateToInt(6, 21, 0));
  max_zodiac.push_back(dateToInt(7, 22, 0));
  max_zodiac.push_back(dateToInt(8, 21, 0));
  max_zodiac.push_back(dateToInt(9, 23, 0));
  max_zodiac.push_back(dateToInt(10, 23, 0));
  max_zodiac.push_back(dateToInt(11, 22, 0));
  max_zodiac.push_back(dateToInt(12, 22, 0));
  max_zodiac.push_back(dateToInt(1, 20, 1));
}

int main() {
  int N;
  cin >> N;
  string s;
  getline(cin, s);
  populate();
  for (int t = 1; t <= N; ++t) {
    cout << t << " ";
    getline(cin, s);
    int m = atoi(string(s, 0, 2).c_str());
    int d = atoi(string(s, 2, 2).c_str());
    int y = atoi(string(s, 4, 4).c_str());
    int jd = dateToInt(m, d, y);
    jd += 40 * 7;
    intToDate(jd, m, d, y);

    cout << setw(2) << setfill('0') << m << "/" << setw(2) << setfill('0') << d
         << "/" << setw(4) << setfill('0') << y << " ";

    jd = dateToInt(m, d, 0);

    bool done = false;
    for (int i = 0; i < zodiacs.size() and not done; ++i) {
      if (jd >= min_zodiac[i] and jd <= max_zodiac[i]) {
        done = true;
        cout << zodiacs[i] << endl;
      }
    }

    if (not done)
      cout << "capricorn" << endl;
  }
}
