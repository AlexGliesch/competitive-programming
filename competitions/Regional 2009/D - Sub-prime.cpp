#include <algorithm>
#include <iostream>
#include <ciso646>
 
using namespace std;

/*
 * Since banks can also sell their debts, just add to the initial money of
 * each bank all the debts owed to it and subtract all the debts it owes.
 * In the end, if any bank has money < 0, then output "no", otherwise output
 * "yes".
 **/
 
int main(){
    ios_base::sync_with_stdio(false);
	int B, N, money[25];
	while (cin >> B >> N, B or N) {
		for (int i = 1; i <= B; ++i) cin >> money[i];
		for (int i = 1; i <= N; ++i) {
			int d, c, v; cin >> d >> c >> v;
			money[d] -= v;
			money[c] += v;
        }

		bool yes = true;
		for (int i = 1; i <= B; ++i) {			
			if (money[i] < 0) {
				yes = false; 
				break;
			}
        }
		cout << (yes ? "S" : "N") << endl;
    }
}