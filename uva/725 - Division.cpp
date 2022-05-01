#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*  */

int main() {
  ios_base::sync_with_stdio(false);

  string all_digits = "0123456789";
  unordered_map<int, vector<pair<int, int>>> all_permutations;

  while (next_permutation(begin(all_digits), end(all_digits))) {
    int num = stoi(string(begin(all_digits), next(begin(all_digits), 5)));
    int den = stoi(string(next(begin(all_digits), 5), end(all_digits)));
    if (num % den == 0)
      all_permutations[num / den].emplace_back(num, den);
  }

  int N;
  bool first = true;
  while (cin >> N, N) {
    if (first)
      first = false;
    else
      cout << '\n';
    auto it = all_permutations.find(N);
    if (it == all_permutations.end()) {
      cout << "There are no solutions for " << N << '.' << endl;
    } else {
      for (auto &p : it->second) {
        cout << setfill('0') << setw(5) << p.first << " / " << setfill('0')
             << setw(5) << p.second << " = " << N << endl;
      }
    }
  }
}