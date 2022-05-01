#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<char> signs;
vector<int> coefs;
set<int> solvs;
bool memo[30][30][6001];

void dp(int i, int p, int s) {
  if (i == coefs.size()) {
    solvs.insert(s);
  } else if (!memo[i][p][(s < 0) ? 3000 - s : s]) {
    int c = p % 2 == 0 ? coefs[i] : -coefs[i];

    for (int j = 0; j <= p; j++) {
      dp(i + 1, p - j, s + c);
    }

    if (signs[i] == '-')
      dp(i + 1, p + 1, s + c);

    memo[i][p][(s < 0) ? 3000 - s : s] = true;
  }
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss;
    ss << line;

    coefs.clear();
    signs.clear();

    int n;
    char c;
    ss >> n;
    coefs.push_back(n);
    signs.push_back('+');

    while (ss >> c >> n) {
      coefs.push_back(c == '+' ? n : -n);
      signs.push_back(c);
    }

    memset(memo, false, sizeof(memo));
    solvs.clear();

    dp(0, 0, 0);
    cout << solvs.size() << endl;
  }

  return 0;
}
