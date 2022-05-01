#include <iostream>
#include <vector>
#include <ciso646>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

/* 
 * use a map to store the last position of a command, starting from the
 * beginning of all commands (this is important). to know the position, you
 * must mark the oldest command as 0, and go up from there.
 * */

ll N;
vector<ll> cmds;
map<ll, ll> pos;

int main() {
	while (cin >> N, N) {
		cmds.clear(); cmds.resize(N + 1);
		pos.clear();
		ll last = 0;
		for (ll i = 1; i <= N; ++i) {
			cin >> cmds[i];
			last = max(last, cmds[i]);
		}
		for (ll i = 1; i <= N; ++i) {
			pos[cmds[i]] = last + 1 - cmds[i];
		}

		ll ans = 0;
		for (ll i = 1; i <= N; ++i) {
			ans += last + 1 - pos[cmds[i]] + (i - 1);
			pos[cmds[i]] = last + i;
		}
		cout << ans << endl;
	}
}