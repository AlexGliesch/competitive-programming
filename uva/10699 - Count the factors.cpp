#include <iostream>
#include <vector>

using namespace std;

/*
 * count number of different prime factors. page 216 of book, 3rd ed.
 **/

int main() {
  vector<int> num_factors(1000010, 0);
  for (int i = 2; i <= 1000000; ++i) {
    if (num_factors[i] == 0) {
      for (int j = i; j <= 1000000; j += i)
        ++num_factors[j];
    }
  }

  int n;
  while (cin >> n, n)
    cout << n << " : " << num_factors[n] << endl;
}