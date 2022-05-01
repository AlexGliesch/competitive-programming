#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <vector>
#define INF 9999999

using namespace std;

/* Use DP, store the results for each [money][garment]*/

vector<vector<int>> model;
vector<vector<int>> dp;
int M, C;

int shop(int money, int i) {
  if (money < 0)
    return INF;
  if (i == C)
    return money;
  if (dp[money][i] == INF) {
    for (int j = 0; j < model[i].size(); ++j) {
      dp[money][i] = min(dp[money][i], shop(money - model[i][j], i + 1));
    }
  }
  return dp[money][i];
}

int main() {
  int N;
  cin >> N;
  for (int t = 0; t < N; ++t) {
    cin >> M >> C;
    model.clear();
    model.resize(C);
    dp.clear();
    dp.resize(210, vector<int>(C, INF));

    for (int i = 0; i < C; ++i) {
      int K;
      cin >> K;
      model[i].resize(K);
      for (int j = 0; j < K; ++j)
        cin >> model[i][j];
    }

    int s = shop(M, 0);
    if (s == INF) {
      cout << "no solution" << endl;
    } else {
      cout << M - s << endl;
    }
  }
}