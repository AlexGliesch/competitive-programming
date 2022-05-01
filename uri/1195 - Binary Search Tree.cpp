#include <algorithm>
#include <iostream>
#include <ciso646>

using namespace std;

/* Very simple. Just construct a BST and run the searches. */

struct bst_node {
	int x;
	bst_node* l = nullptr;
	bst_node* r = nullptr;
};

void add_tree(int x, bst_node*& tree) {
	if (tree == nullptr) {
		tree = new bst_node;
		tree->x = x;
	} else {
		if (x >= tree->x) add_tree(x, tree->r);
		else add_tree(x, tree->l);
	}
}

void pre_order(const bst_node& tree) {
	cout << ' ' << tree.x;
	if (tree.l) pre_order(*tree.l);
	if (tree.r) pre_order(*tree.r);
}

void post_order(const bst_node& tree) {
	if (tree.l) post_order(*tree.l);
	if (tree.r) post_order(*tree.r);
	cout << ' ' << tree.x;	
}

void in_order(const bst_node& tree) {
	if (tree.l) in_order(*tree.l);
	cout << ' ' << tree.x;
	if (tree.r) in_order(*tree.r);
}

int main() {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		int n; cin >> n;
		bst_node* tree = nullptr;
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			add_tree(x, tree);
		}
		cout << "Case " << t + 1 << ":" << endl;

		cout << "Pre.:";
		pre_order(*tree);
		cout << endl;

		cout << "In..:";
		in_order(*tree);
		cout << endl;

		cout << "Post:";
		post_order(*tree);
		cout << endl;

		cout << endl;
	}
}