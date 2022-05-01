#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <ciso646>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> ll2;

/* 
 * very nice problem, dijsktra + dp.
 * 
 * to kill each monster with a given hp, you have the following recurrence: * 
 * kill(spell_id, hp_left):
 *		if (hp <= 0) return 0
 *		if (spell_id >= #spells) return INFINITY
 *		return min(mana[spell_id] + kill(spell_id, hp_left - damage[spell_id]),
 *				   kill(spell_id + 1, hp_left))
 *				   
 * you should dp that on both input parameters. note that the same dp is used
 * to solve the problem for all the monsters!
 *				   
 * having that figured out, we need to run a dijkstra on the graph, where the
 * weight of an edge is the sum of mana needed to kill all the monsters in the
 * node that that edge leads to. a dijkstra is needed because, if zak galou can
 * skip one or more rooms to reach the treasure, he should. don't forget that
 * the initial node of the dijkstra should also contain the mana needed to kill
 * the mosnters in the original room.
 * 
 * the minimum distance returned by the algorithm is the answer.
 * 
 * */

ll num_spells, num_rooms, num_galleries, num_monsters, mana[1010], damage[1010],
	hp_monster[1010], dp_room[1010], dp_monster[1010][1010], dist[1010];
vector<ll> g[1010], monsters_in_room[1010];

ll kill_monster(ll Si, ll hp) {
	if (hp <= 0) return 0;
	if (Si >= num_spells) return (1LL << 40LL);
	if (dp_monster[Si][hp] == -1) {
		dp_monster[Si][hp] = min(
			mana[Si] + kill_monster(Si, hp - damage[Si]),
			kill_monster(Si + 1, hp));
	}
	return dp_monster[Si][hp];
}

ll kill_monsters_in_room(ll v) {
	if (dp_room[v] == -1) {
		dp_room[v] = 0;
		for (ll i = 0; i < monsters_in_room[v].size(); ++i)
			dp_room[v] += kill_monster(0, 
				hp_monster[monsters_in_room[v][i]]);
	}
	return dp_room[v];
}

ll dijkstra() {
	memset(dist, -1, sizeof dist);
	memset(dp_room, -1, sizeof dp_room);
	memset(dp_monster, -1, sizeof dp_monster);

	priority_queue<ll2> pq;
	dist[0] = kill_monsters_in_room(0);
	pq.push(ll2(-dist[0], 0));

	while (pq.size()) {
		ll v = pq.top().second, d = -pq.top().first; pq.pop();
		if (dist[v] != d) continue;
		if (v == num_rooms - 1) return d;		

		for (ll i = 0; i < g[v].size(); ++i) {
			ll u = g[v][i];
			ll cd = d + kill_monsters_in_room(u);
			if (dist[u] == -1 or dist[u] > cd) {
				dist[u] = cd;
				pq.push(ll2(-cd, u));
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> num_spells >> num_rooms >> num_galleries >> num_monsters) {
		if (num_spells == 0 and num_rooms == 0 and 
			num_galleries == 0 and num_monsters == 0) break;

		for (ll i = 0; i < num_rooms; ++i) {
			g[i].clear();
			monsters_in_room[i].clear();
		}

		for (ll i = 0; i < num_spells; ++i) 
			cin >> mana[i] >> damage[i];		

		for (ll i = 0; i < num_galleries; ++i) {
			ll A, B; cin >> A >> B; --A, --B;
			g[A].push_back(B);
			g[B].push_back(A);
		}

		for (ll i = 0; i < num_monsters; ++i) {
			ll R; cin >> R; --R;
			monsters_in_room[R].push_back(i);
			cin >> hp_monster[i];
		}

		ll ans = dijkstra();
		cout << ans << endl;
	}
}