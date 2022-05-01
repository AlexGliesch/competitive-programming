#include <string>
#include <iostream>

using namespace std;

/* 
 * the idea: given a string index, count how many substrings end there having
 * each of the possible remainders of 3: 0, 1 or 2.
 * 
 * for example, given the string 20142, at the endpoint 2:
 * -> 2 strings end at 2, with %3=0: '20142' and '42'
 * -> 2 strings end at 2, with %3=1: '142' and '0142'
 * -> 1 string ends at 2 with %3=2: '2'
 * 
 * we are interested only in the substrings that with %3=0. namely, we want
 * the sum of all the numbers of substrings that end with %3=0,
 * for all possible (valid) indices in the given string.
 * 
 * say we have a current string x, and denote r0 as the number of substrings
 * ending at x with %3=0, r1 and r2 with %3=1 and %3=2, respectively. if the
 * next character of x is c, we can know the next r0, r1 and r2 of x+{c} through
 * the following table:
 *         _________________________
 *		   | c%3=0 | c%3=1 | c%3=2 |
 *  ________________________________
 *	new_r0 | r0+1  |  r2   |  r1   |
 *	________________________________
 *  new_r1 |  r1   |  r0+1 |  r2   |
 *  ________________________________
 *  new_r2 |  r2   |  r1   | r0+1  |
 *  ________________________________
 *  
 *  so, for each new character, update the values of r0, r1 and r2 and add
 *  r0 to the final answer. if you find a character that is not a number, 
 *  set all r0, r1 and r2 to 0, and start again when you find a digit.
 *  
 *  ps: USE LONG LONG
 * */

int main() {
	ios_base::sync_with_stdio(false);
	string s;
	while (cin >> s) {
		long long ans = 0;
		int r0 = 0, r1 = 0, r2 = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (isalpha(s[i])) {
				r0 = r1 = r2 = 0;
			} else {
				int k = (s[i] - '0') % 3;
				if (k == 0) {
					++r0;
				} else if (k == 1) {
					int old_r0 = r0;
					r0 = r2;
					r2 = r1;
					r1 = old_r0 + 1;
				} else if (k == 2) {
					int old_r0 = r0;
					r0 = r1;
					r1 = r2;
					r2 = old_r0 + 1;
				}
				ans += r0;
			}
		}
		cout << ans << endl;
	}
}