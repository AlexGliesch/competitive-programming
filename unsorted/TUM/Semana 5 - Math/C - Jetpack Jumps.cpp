#include <iostream>
#include <cmath>
using namespace std;

long long t, k, hi, lo, mid;
long double f, val;

long long bsearch() {
    lo = 0, hi = 1000000000;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        val = (mid * (mid + 1) * (2.0L * mid + 1)) / 6.0L;
        if (abs(val - f) < 0.05)
            return mid;
        else if (val < f)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return hi;
}

int main() {
    cin >> t;
    for (k = 1; k <= t; ++k) {
        cin >> f;
        cout << "Case #" << k << ": " << bsearch() + 2 << endl;
    }
}