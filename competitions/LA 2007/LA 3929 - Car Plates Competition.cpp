#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>

using namespace std;
typedef long long ll;

/* 
 * Once you learn to calculate the integer value of a plaque, the problem
 * is easy. The integer value of an old type plaque ABC1234 is 
 * 4 + 3*10 + 2*100 + 1*1000 + C*10000 + B*10000*21 + A*10000*21^2. 
 * The integer value of a new type plaque ABCDE12 is
 * 2 + 1*10 + E*100 + D*100*21 + C*100*21^2 + B*100*21^3 +A*100*21^4.
 * 
 * The values for each letter c are, for the old plaque, c - 'A'. For the new 
 * plaque, I found the values by enumerating all letters except ACMIP in a 
 * switch-case.
 * 
 * Use long long.
 */

struct IsUpper { bool operator()(char c) { return isupper(c); } };

string Si, Sm;
ll C;

ll letterValue5(char c) {
	switch(c) {
		case 'B': return 0;
		case 'D': return 1;
		case 'E': return 2;
		case 'F': return 3;
		case 'G': return 4;
		case 'H': return 5;			
		case 'J': return 6;
		case 'K': return 7;
		case 'L': return 8;
		case 'N': return 9;
		case 'O': return 10;
		case 'Q': return 11;
		case 'R': return 12;
		case 'S': return 13;
		case 'T': return 14;
		case 'U': return 15;
		case 'V': return 16;
		case 'W': return 17;
		case 'X': return 18;
		case 'Y': return 19;
		case 'Z': return 20;
		default: return c - '0';
	}
}

ll letterValue3(char c) {
	if (isalpha(c)) return c - 'A';
	else return c - '0';
}

ll value(const string& s) {
	ll ans = 0;
	ll nUpper = count_if(s.begin(), s.end(), IsUpper());
	if (nUpper == 3) {
		ans = letterValue3(s[6]) 
		+ letterValue3(s[5]) * 10 
		+ letterValue3(s[4]) * 100
		+ letterValue3(s[3]) * 1000
		+ letterValue3(s[2]) * 10000
		+ letterValue3(s[1]) * 10000 * 26
		+ letterValue3(s[0]) * 10000 * 26 * 26;
	} else { //if (nUpper == 5) 
		ans = letterValue5(s[6]) 
		+ letterValue5(s[5]) * 10 
		+ letterValue5(s[4]) * 100
		+ letterValue5(s[3]) * 100 * 21
		+ letterValue5(s[2]) * 100 * 21 * 21
		+ letterValue5(s[1]) * 100 * 21 * 21 * 21
		+ letterValue5(s[0]) * 100 * 21 * 21 * 21 * 21;		
		ans += 1 + value("ZZZ9999");
	}
	return ans;
}

bool valid() {
	ll nUpperi = count_if(Si.begin(), Si.end(), IsUpper());
	if (nUpperi != 3 and nUpperi != 5) 		
		return false;	
	
	if (nUpperi == 5 and Si.find_first_of("ACMIP") != string::npos) 		
		return false;	
	
	ll nUpperm = count_if(Sm.begin(), Sm.end(), IsUpper());
	ll vm = value(Sm), vi = value(Si);
		
	if (vm >= vi) return false;	
	if (vi - vm > C) return false;	
	
	return true;
}

int main() {
	while (cin >> Sm >> Si >> C, Sm != "*") {		
		cout << (valid() ? "Y" : "N") << endl;
	}
}