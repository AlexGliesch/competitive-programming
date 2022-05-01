#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/* I don't know why WA; toolkit doesn't output weird values, but people
 * on the forum say it's not a problem...*/

int main() {
	ios_base::sync_with_stdio(false);
	string s; getline(cin, s);
	while (getline(cin, s)) {
		for (auto& c : s) {
			if (isalpha(c)) c += 3;
		}
		reverse(begin(s), end(s));
		for (int i = s.size() / 2; i < s.size(); ++i) 
			--s[i];
		cout << s << endl;
	}
}