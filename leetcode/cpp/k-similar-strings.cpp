class Solution {
public:
  // binom(20, 6) ~= 40000
  // A*  
  
  int kSimilarity(string s1, string s2) {    
    map<string, pair<int, int>> dist;
    priority_queue<pair<int, string>> pq;
    auto heuristic = [&](const string& s) {
      int mis = 0;
      for (int i = 0; i < s.size(); ++i) mis += s[i] != s2[i];
      return mis / 2;
    };    
    pq.emplace(-heuristic(s1), s1);
    dist[s1] = pair(0, heuristic(s1));
    while (!pq.empty()) {
      auto p = pq.top();
      pq.pop();
      string s = p.second;      
      int g = dist[s].first, h = dist[s].second;
      if (-p.first != g + h) continue;
        
      if (s == s2) return g;
      for (int i = 0; i < s.size(); ++i) 
        if (s[i] != s2[i]) {
          for (int j = i + 1; j < s.size(); ++j) 
            if (s[j] == s2[i]) {
              swap(s[i], s[j]);
              if (dist.count(s) == 0 || dist[s].first > g + 1) {
                int h = heuristic(s);
                dist[s] = pair(g + 1, h);
                pq.emplace(-(g + 1 + h), s);
              }
              swap(s[i], s[j]);           
            }
          break;
        }
    }    
    return -1;
  }
};