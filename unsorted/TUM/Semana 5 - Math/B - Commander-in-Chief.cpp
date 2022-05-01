#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t, k, n, i, j, ans;
    cin >> t;
    for (k = 1; k <= t; ++k) {
        cin >> n >> ans;
        for (j = 1; j < n; ++j) {
            cin >> i;
            ans = __gcd(ans, i);
        }
        cout << "Case #" << k << ": " << ans << endl;
    }
}