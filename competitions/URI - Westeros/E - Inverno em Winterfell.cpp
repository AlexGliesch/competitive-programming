#include <iostream>
#include <algorithm>
#include <vector>
#include <ciso646>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#define INF (1<<28)
#define MAX 1010

using namespace std;
typedef long long ll;

/* 2D segment tree node */
struct Point {
    ll x, y, mx;
    Point() {}
    Point(ll x, ll y, ll mx) : x(x), y(y), mx(mx) { } 
    bool operator<(const Point& other) const {
        return mx < other.mx;
    }
};
 
struct SegTree2D {
private:
	Point T[2 * MAX * MAX];
    ll n, m;
 
	Point build(ll node, ll a1, ll b1, ll a2, ll b2, ll P[MAX][MAX]) {
        if (a1 > a2 or b1 > b2)
            return def();

        if (a1 == a2 and b1 == b2)
            return T[node] = Point(a1, b1, P[a1][b1]);
 
        T[node] = def();
        T[node] = maxNode(T[node], build(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, P));
        T[node] = maxNode(T[node], build(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, P));
        T[node] = maxNode(T[node], build(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, P));
        T[node] = maxNode(T[node], build(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, P));
        return T[node];
    }
 
    Point query(ll node, ll a1, ll b1, ll a2, ll b2, ll x1, ll y1, ll x2, ll y2) {
        if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2)
            return def();
        if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2)
            return T[node];
        Point mx = def();
        mx = maxNode(mx, query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2));
        return mx;
    }
 
    Point update(ll node, ll a1, ll b1, ll a2, ll b2, ll x, ll y, ll value) {
        if (a1 > a2 or b1 > b2)
            return def();
 
        if (x > a2 or y > b2 or x < a1 or y < b1)
            return T[node];
 
        if (x == a1 and y == b1 and x == a2 and y == b2)
            return T[node] = Point(x, y, value);
 
        Point mx = def();
        mx = maxNode(mx, update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x, y, value) );
        mx = maxNode(mx, update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x, y, value));
        mx = maxNode(mx, update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x, y, value));
        mx = maxNode(mx, update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x, y, value) );
        return T[node] = mx;
    }
 
public:

	/* 
	 * initialize and construct segment tree from grid of values P with size 
	 * n x m
	 * */
	void init(ll n, ll m, ll P[MAX][MAX]) {
		this->n = n;
		this->m = m;
		build(1, 1, 1, n, m, P);
	}

	/* query from range [ (x1, y1), (x2, y2) ]
	* Time: O(logn) */
	Point query(ll x1, ll y1, ll x2, ll y2) {
		return query(1, 1, 1, n, m, x1, y1, x2, y2);
	}

    /* update the value of (x, y) index to 'value'
    * Time: O(logn) */
    Point update(ll x, ll y, ll value) {
        return update(1, 1, 1, n, m, x, y, value);
    }
 
    /* utility functions; these functions are virtual because they will be 
       overridden in child class */
    Point maxNode(Point a, Point b) {
		return Point(0, 0, a.mx + b.mx);
    }
 
    /* dummy node */ 
    Point def() {
        return Point(0, 0, 0);
    }
};

ll binom(ll n, ll k) {
	ll ans = 1;
	if (k > n - 1) k = n - 1;
	for (ll i = 0; i < k; ++i) {
		ans *= (n - i);
		ans %= 1000000007;
		ans /= (i + 1);
		ans %= 1000000007;
	}
	ans %= 1000000007;
	return ans;
}

ll P[MAX][MAX], n, m, i;
SegTree2D st;

int main() {	
	memset(P, 0, sizeof P);	
	cin >> n >> m;	
	st.init(n+1, m+1, P); 

	string s; getline(cin, s);
	int day = 1;
	while (getline(cin, s)) {
		istringstream ss(s);
		vector<ll> in;
		while (ss >> i) in.push_back(i);
		if (in.size() == 3) {
			ll x = in[0], y = in[1], b = in[2];
			st.update(x, y, P[x][y] + b);
			P[x][y] += b;
		} else if (in.size() == 2) {
			ll x = in[0], y = in[1];
			st.update(x, y, 0);
			P[x][y] = 0;
		} else if (in.size() == 5) {			
			ll x1 = in[0], y1 = in[1], x2 = in[2], y2 = in[3], c = in[4];			
			ll snowmen = st.query(x1, y1, x2, y2).mx;
			//Combinação com repetição
			cout << "Day #" << day++ << ": " << binom(snowmen+c-1, c) << endl;
		}
	}
}