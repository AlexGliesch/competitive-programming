#include <iostream>
#include <string>
using namespace std;

int main() {
    int t, r, x, m, i, k;
    cin >> t;
    for (k = 1; k <= t; ++k) {
        string s;
        cin >> s;
        x = 0, m = 1;
        for (i = s.size() - 1; i >= 0; --i) {
            x = (x + m * (s[i] - '0')) % 13;
            m = (m * 8) % 13;
        }
        x = (x + 3) % 13;
        cout << "Case #" << k << ": " << (x ? x : 13) << endl;
    }
}