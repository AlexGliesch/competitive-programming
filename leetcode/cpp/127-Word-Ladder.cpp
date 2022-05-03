class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    auto wl = wordList;
    sort(begin(wl), end(wl));
    if (binary_search(begin(wl), end(wl), endWord) == false) return 0;

    queue<string> q;
    map<string, int> dist;
    dist[beginWord] = 1;
    q.push(beginWord);

    while (q.size()) {
      string s = q.front();
      q.pop();
      if (s == endWord) return dist[s];

      for (int i = 0; i < s.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
          char old = s[i];
          if (old == c) continue;
          int d = dist[s];
          s[i] = c;
          if (binary_search(begin(wl), end(wl), s) && dist.count(s) == 0) {
            dist[s] = d + 1;
            q.push(s);
          }
          s[i] = old;
        }
      }
    }
    return 0;
  }
};