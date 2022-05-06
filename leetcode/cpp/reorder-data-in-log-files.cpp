#include "includes.h"

class Solution {
public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    int numberofletterlogs = logs.size();
    vector<bool> isletterlog(logs.size(), true);
    for (int i = 0; i < logs.size(); ++i) {
      int j = logs[i].find_first_of(' ');
      if (logs[i][j + 1] >= '0' && logs[i][j + 1] <= '9') {
        isletterlog[i] = false;
        --numberofletterlogs;
      }
    }
    vector<int> is(logs.size()); // indices from 0 to logs.size
    iota(begin(is), end(is), 0);
    stable_sort(begin(is), end(is),
                [&](int i, int j) { return isletterlog[i] > isletterlog[j]; });

    sort(begin(is), begin(is) + numberofletterlogs, [&](int i, int j) {
      string iid = string(logs[i].begin(), logs[i].begin() + logs[i].find(' '));
      string icontents =
          string(logs[i].begin() + logs[i].find(' '), logs[i].end());
      string jid = string(logs[j].begin(), logs[j].begin() + logs[j].find(' '));
      string jcontents =
          string(logs[j].begin() + logs[j].find(' '), logs[j].end());
      return tie(icontents, iid) < tie(jcontents, jid);
    });

    vector<string> ll;
    for (auto i : is)
      ll.push_back(logs[i]);
    return ll;
  }
};

int main() {
  Solution s;
  vector<string> v{"a1 9 2 3 1", "g1 act car", "zo4 4 7", "ab1 off key dog",
                   "a8 act zoo"};
  auto r = s.reorderLogFiles(v);
  for (auto s : r)
    cout << s << endl;
}