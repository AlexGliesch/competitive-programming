#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef long long int lli;

vector<pair<lli, lli> > pos;
struct Node {
  int l, r;
  vector<int> children;
  map<int, set<int> > value;
  Node(int l_, int r_) {
    l = l_; r = r_;
    if (r-l>1)
      children.assign(2, -1);
  }
};
vector<Node> tree;
void buildTree(int w, int h) {
  tree.assign(1, Node(0, w+h+1));
  for (int i=0; i<tree.size(); ++i)
    if (tree[i].r-tree[i].l > 1) {
      int m = (tree[i].l + tree[i].r)/2;
      tree[i].children[0] = tree.size();
      tree.emplace_back(tree[i].l, m);
      tree[i].children[1] = tree.size();
      tree.emplace_back(m, tree[i].r);
    }
}
void add(int p, int amt, int n=0) {
  int x = pos[p].first+pos[p].second, y = pos[p].first-pos[p].second;
  if (tree[n].l > x || tree[n].r <= x)
    return;
  if (amt == 1)
    tree[n].value[y].insert(p);
  else
    tree[n].value[y].erase(p);
  if (tree[n].value[y].empty())
    tree[n].value.erase(y);
  for (int c : tree[n].children)
    add(p, amt, c);
}
vector<int> result;
void query(int minx, int miny, int maxx, int maxy, int n=0) {
  if (tree[n].l > maxx || tree[n].r <= minx || tree[n].value.empty())
    return;
  minx = max(minx, tree[n].l);
  maxx = min(maxx, tree[n].r-1);
  if (minx == tree[n].l && maxx == tree[n].r-1) {
    for (auto it = tree[n].value.lower_bound(miny); it != tree[n].value.upper_bound(maxy); ++it)
      for (auto it2 = it->second.begin(); it2!=it->second.end(); ++it2)
        result.push_back(*it2);
  } else {
    for (int c : tree[n].children)
      query(minx, miny, maxx, maxy, c);
  }
}

int main() {
  int t;
  cin >> t;
  for (int ta=0; ta<t; ++ta) {
    cout << "Case #" << ta+1 << ":\n";
    int n, q;
    lli w, h;
    cin >> n >> q >> w >> h;
    buildTree(w, h);
    pos.resize(n);
    for (int i=0; i<n; ++i) {
      cin >> pos[i].first >> pos[i].second;
      add(i, 1);
    }
    for (int qa=0; qa<q; ++qa) {
      int x, y, r;
      cin >> x >> y >> r;
      result.clear();
      query(x+y-r, x-y-r, x+y+r, x-y+r);
      lli a, b, c, d, e, f;
      cin >> a >> b >> c >> d >> e >> f;
      for (lli i : result) {
        add(i, -1);
        pair<lli, lli> nextPos((pos[i].first*a+pos[i].second*b+(i+1)*c)%w, (pos[i].first*d+pos[i].second*e+(i+1)*f)%h);
        pos[i] = nextPos;
        add(i, 1);
      }
    }
    for (auto p : pos)
      cout << p.first << ' ' << p.second << '\n';
  }
}