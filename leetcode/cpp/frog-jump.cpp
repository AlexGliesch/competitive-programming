class Solution {
public:
  bool canCross(vector<int>& stones) {
    if (stones[1] != 1) return false;
    set<pair<int, int>> visited;
    queue<pair<int, int>> q;
    q.emplace(1, 1);
    visited.emplace(1, 1);
    while (!q.empty()) {
      int pos = q.front().first;
      int k = q.front().second;
      q.pop();
      assert(pos >= stones[0] && pos <= stones.back());
      if (pos == stones.back())
        return true;      
      for (int j = k - 1; j <= k + 1; ++j) {
        if (j <= 0) continue;
        int jump = pos + j;
        if (binary_search(begin(stones), end(stones), jump) && 
           visited.count(pair(jump, j)) == 0) {
          q.emplace(jump, j);
          visited.emplace(jump, j);
        }
      }
    }
    return false;
  }
};