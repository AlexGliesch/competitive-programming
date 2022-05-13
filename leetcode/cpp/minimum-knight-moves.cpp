class Solution {
public:
  // A* with heuristic = manhattan distance / 3 
  // but BFS probably works for the problem size
  struct State {
    State(int r, int c, int g, int h) : r(r), c(c), g(g), h(h) { }
    int r, c;
    int g, h;
    bool operator<(const State& s) const { return g + h > s.g + s.h; }    
  };
  
  int minKnightMoves(int x, int y) {
    const int dr[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    const int dc[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    
    auto manDist = [&](int r, int c) {
      return abs(r - x) + abs(c - y);
    };
    
    map<pair<int, int>, int> dist; // Can probably figure out a way 
                                   // to use a vector/matrix if we
                                   // want to optimize
    priority_queue<State> pq; 
    
    dist[pair(0, 0)] = 0;
    pq.emplace(0, 0, 0, (x + y) / 3); // dist=modulo?
    while (pq.size()) {
      State s = pq.top();
      pq.pop();
      assert(dist.count(pair(s.r, s.c)));
      if (s.g != dist[pair(s.r, s.c)]) continue;
      if (s.r == x and s.c == y) {
        return s.g;
      }
      
      for (int i = 0; i < 8; ++i) {
        int r = s.r + dr[i], c = s.c + dc[i];        
        int g = s.g + 1;
        int h = manDist(r, c) / 3;
        if (dist.count(pair(r, c)) == 0 || dist[pair(r, c)] > g) {
          dist[pair(r, c)] = g;
          pq.emplace(r, c, g, h);
        }
      }      
    }
    return -1;    
  }
};