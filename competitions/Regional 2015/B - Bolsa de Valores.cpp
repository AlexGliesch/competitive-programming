#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

/* 
 * DP, where the state is (p, a): p is the current index in the values vector, 
 * and a is whether he has a stock at the moment or not. the solution is 
 * f(p, a):
 *    if (p >= N) -> 0
 *    if (a == 1) -> max(f(p+1, 1), v[p] + f(p+1, 0))
 *    if (a == 0) -> max(f(p+1, 0), -C -v[p] + f(p+1, 1))
 *    
 * at every point, if he has a stock he can choose whether to sell it or 
 * to keep it. if he doesn't have one, he can choose whether to buy it or 
 * to stay without one. 
 * */

int dp[200050][2];
int v[200050];
int N, C;

int f(int p, int a) {
    if (p >= N) return 0;
    if (dp[p][a] == -1) {
        if (a == 1) dp[p][a] = max(f(p+1, 1), v[p] + f(p+1, 0));
        else dp[p][a] = max(f(p+1, 0), -C - v[p] + f(p+1, 1));
    }
    return dp[p][a];
}

int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> N >> C) {
        for (int i = 0; i < N; ++i){
            cin >> v[i];
        }

        memset(dp, -1, sizeof dp);
        cout << f(0, 0) << endl;
    }
}
