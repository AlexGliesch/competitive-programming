class Solution {
public:
  vector<int> sortArrayByParityII(vector<int>& nums) {
    auto nn = nums;
    sort(begin(nn), end(nn), [&](int i, int j) { return (i % 2) < (j % 2); });
    int n = nn.size() / 2;
    for (int i = 1, j = n % 2; i < n; i += 2, j += 2) {
      swap(nn[i], nn[j + n]);
    }
    return nn;
  }
};