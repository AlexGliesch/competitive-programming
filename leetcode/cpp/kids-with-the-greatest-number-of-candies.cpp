class Solution {
public:
  vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int max = *max_element(begin(candies), end(candies));
    vector<bool> ans(candies.size());
    for (int i = 0; i < ans.size(); ++i) {
      ans[i] = (candies[i] + extraCandies >= max);
    }
    return ans;
  }
};