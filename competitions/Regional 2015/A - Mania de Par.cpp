#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/* 
 * easy: dijkstra where the state is the current vertex and a boolean that says
 * whether it was visited with an even or odd number of edges . 
 * */

struct State {
    int v, w, p;
    State(int v = 0, int w = 0, int p = 0) : v(v), w(w), p(p) {}
    bool operator<(const State& s) const {
        return w > s.w or (w == s.w and p > s.p);
    }
};

int C, V;
vector<vector<State>> g;

int dijkstra(int s, int t) {
    vector<vector<int>> dist(C, vector<int>(2, (1<<28)));
    priority_queue<State> pq;

    pq.push(State(s, 0, 0));
    dist[s][0] = 0;
    while (pq.size()) {
        State s = pq.top(); pq.pop();

        if (dist[s.v][s.p] != s.w) continue;
        if (s.v == t and s.p == 0) return s.w;

        for (int i = 0; i < g[s.v].size(); ++i) {
            State ns(g[s.v][i].v, s.w + g[s.v][i].w, 1-s.p);
            if (dist[ns.v][ns.p] > ns.w) {
                dist[ns.v][ns.p] = ns.w;
                pq.push(ns);
            }
        }
    }

    return -1;
}

int main() {
    while (cin >> C >> V) {
        g.clear(); g.resize(C);
        for (int i = 0; i < V; ++i){
            int C1, C2, G; cin >> C1 >> C2 >> G; --C1, --C2;
            g[C1].push_back(State(C2, G, 0));
            g[C2].push_back(State(C1, G, 0));
        }
        cout << dijkstra(0, C-1) << endl;
    }
}
