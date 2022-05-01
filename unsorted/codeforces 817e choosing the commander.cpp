#include <iostream>
#include <vector>
using namespace std;

struct Node {
  vector<int> children;
  int value, bit;
  Node(int b) {
    children.assign(2, -1);
    value = 0;
    bit = b;
  }
};
vector<Node> tree;

void add(int id, int amt, int n) {
  tree[n].value += amt;
  if (tree[n].bit == 0)
    return;
  int next = id / tree[n].bit;
  if (tree[n].children[next] == -1) {
    tree[n].children[next] = tree.size();
    tree.emplace_back(tree[n].bit/2);
  }
  add(id & (tree[n].bit-1), amt, tree[n].children[next]);
}

int query(int id, int l, int n) {
  if (tree[n].bit == 0)
    return 0;
  int nextId = id & (tree[n].bit-1);
  int nextL = l & (tree[n].bit-1);
  int child = (id^l)/tree[n].bit;
  int result = 0;
  if (l&tree[n].bit) {
    int rChild = tree[n].children[1-child];
    if (rChild != -1)
      result += tree[rChild].value;
  }
  if (tree[n].children[child] != -1)
    result += query(nextId, nextL, tree[n].children[child]);
  return result;
}

int main() {
  tree.emplace_back(1<<30);
  int q;
  cin >> q;
  for (int qa=0; qa<q; ++qa) {
    int type;
    cin >> type;
    if (type < 3) {
      int p;
      cin >> p;
      add(p, type==1 ? 1 : -1, 0);
    } else {
      int p, l;
      cin >> p >> l;
      cout << query(p, l, 0) << endl;
    }
  }
}