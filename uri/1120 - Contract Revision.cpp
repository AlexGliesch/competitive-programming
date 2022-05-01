#include <ciso646>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	string rem, num;
	while (cin >> rem >> num) {
		if (rem == "0" and num == "0") break;
		num.erase(remove(begin(num), end(num), rem[0]), end(num));
		while (num[0] == '0') num.erase(0, 1);
		if (num.empty()) cout << 0 << endl;
		else cout << num << endl;
	}
}