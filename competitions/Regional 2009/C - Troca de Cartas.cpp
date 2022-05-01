#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ciso646>

using namespace std;

/* 
 * Put all cards of A in a set Sa, and all cards of B in a set Sb (i.e., 
 * eliminate duplicates). Then, take the intersection I of Sa and Sb.
 * You can use std::set_intersection for that. The answer is 
 * min(Sa.size(), Sb.size()) - I.size().
 * */

int main(){
	int A, B;
	vector<int> I(10010);
	while (cin >> A >> B, A or B) {
		set<int> Sa, Sb;
		for (int i = 0; i < A; ++i) {
			int x; cin >> x;
			Sa.insert(x);
		}

		for (int i = 0; i < B; ++i) {
			int x; cin >> x;
			Sb.insert(x);
		}

		int n = set_intersection(Sa.begin(), Sa.end(), 
			Sb.begin(), Sb.end(), I.begin()) - I.begin();

		cout << min(Sa.size(), Sb.size()) - n << endl;
	}
}