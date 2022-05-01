#include <bitset>
#include <cmath>
#include <iostream>
#include <vector>

#define LOG2(X)                                                                \
  ((unsigned)(8 * sizeof(unsigned long long) - __builtin_clzll((X)) - 1))

using namespace std;

typedef vector<long long> vll;

long long countOnes(long long n) {
  long long s = 0, i = 0;

  while (n > 0) {
    long long p = (long long)LOG2(n);
    s += 1 + p * ((long long)1 << (p - 1)) + i * ((long long)1 << p);
    n = n % ((long long)1 << p);
    i++;
  }

  return s;
}

int main() {
  long long a, b;
  while (cin >> a >> b) {
    cout << countOnes(b) - countOnes(a - 1) << endl;
  }
  return 0;
}