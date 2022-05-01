#include <iostream>
#include <string>
#include <vector>

using namespace std;

string keys[] = {" 0 0", ".,?\"", "abc2",  "def3", "ghi4",
                 "jkl5", "mno6",  "pqrs7", "tuv8", "wxyz9"};

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int L;
    cin >> L;

    vector<int> N(L), P(L);
    for (int i = 0; i < L; ++i)
      cin >> N[i];
    for (int i = 0; i < L; ++i)
      cin >> P[i];

    string s(L, '\0');
    for (int i = 0; i < L; ++i) {
      s[i] = keys[N[i]][P[i] - 1];
    }
    cout << s << endl;
  }
}
