#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  while (cin >> n) {
    long long total = 0;
    vector<int> notes;
    for (int i = 0; i < n; i++) {
      int s;
      cin >> s;
      notes.push_back(s);
      total += s;
    }
    long long average = total / notes.size();
    if (average * notes.size() != total) {
      cout << -1 << '\n';
    } else {
      long long increments = 0;
      for (int n : notes) {
        if (n < average) {
          increments += average - n;
        }
      }
      cout << increments + 1 << '\n';
    }
  }
  return 0;
}