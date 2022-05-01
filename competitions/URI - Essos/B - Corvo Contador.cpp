#include <string>
#include <iostream>

using namespace std;

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {	
		if (s == "caw") {
			cin >> s;
			cout << ans << endl;
			ans = 0;
		} else {
			if (s[0] == '*') ans += 4;
			if (s[1] == '*') ans += 2;
			if (s[2] == '*') ans += 1;
		}
	}
}