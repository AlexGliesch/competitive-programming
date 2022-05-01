#include <iostream>
#include <vector>
#include <set>
#include <ciso646>
#include <algorithm>

using namespace std;
typedef vector<int> vi;

/* 
 * programming, straightforward, not much to say. just pay attention to the
 * details and program the card interactions as they say, and you'll probably
 * get it correct.
 * */

int N, J;
vi deck;
vector<vi> mounts;
set<int> discard;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N >> J, not(N == 0 and J == 0)) {
		deck.clear(); deck.resize(N);
		mounts.clear(); mounts.resize(J + 1);
		discard.clear();
		for (int i = 0; i < N; ++i) cin >> deck[(N - 1) - i];

		int k = 1;
		while(true){
			if (deck.empty()) break;
			int card = deck.back();	deck.pop_back();

			/* discard pile */
			if (discard.find(card) != discard.end()) {
				discard.erase(card);
				mounts[k].push_back(card);
				mounts[k].push_back(card);
				continue;
			}

			/* check other players mounts */
			bool another = false;
			for (int i = 1; i <= J; ++i) {
				if (i != k and mounts[i].size() and mounts[i].back() == card) {
					for (int j = 0; j < mounts[i].size(); ++j) {
						mounts[k].push_back(mounts[i][j]);
					}
					mounts[i].clear();
					another = true;
				}				
			}

			if (another) {
				mounts[k].push_back(card);
				continue;
			}

			/* check if its the same as current mount*/
			if (mounts[k].size() and mounts[k].back() == card) {
				mounts[k].push_back(card);
				continue;	
			}

			/* otherwise, discard */
			discard.insert(card);
			k = (((k - 1) + 1) % J) + 1;
		}

		int largest = 0;
		for (int i = 1; i <= J; ++i) {			
			largest = max(largest, (int)mounts[i].size());
		}

		cout << largest;
		for (int i = 1; i <= J; ++i) {
			if (mounts[i].size() == largest)
				cout << ' ' << i;
		}
		cout << endl;
	}
}