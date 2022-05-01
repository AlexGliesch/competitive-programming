#include <algorithm>
#include <iostream>
#include <ciso646>
#include <string>

using namespace std;

/* Procedure to remove a node of a BST:
 * 
 * locate the node
 * if it's a leaf:
 *		just remove it
 * if it only has one child:
 *		link the parent to the child
 * if it has two children:
 *		the node receives the value of the largest node in its left sub-tree
 *		remove (recursively)the largest node in the left sub-tree
 *		
 * All the rest is easy and straightforward.	
 *	*/

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

bst_node*& find_tree(int x, bst_node*& tree) {
	if (tree) {
		if (tree->x == x) return tree; 
		else if (x > tree->x) return find_tree(x, tree->r);
		else return find_tree(x, tree->l);
	} else {
		static bst_node* n = nullptr;
		return n;
	}
}

bst_node*& find_largest(bst_node*& tree) {
	if (tree->r) return find_largest(tree->r);
	return tree;
}

void remove_tree(int x, bst_node*& tree) {
	auto& n = find_tree(x, tree);
	if (n != nullptr) {
		if (not n->r and not n->l) { n = nullptr; }
		else if (n->r and not n->l) { n = n->r; }
		else if (n->l and not n->r) { n = n->l; }
		else {			
			n->x = find_largest(n->l)->x;
			remove_tree(n->x, n->l);
		}
	}	
}

bool visited_first = false;

void pre_order(const bst_node& tree) {
	if (visited_first) cout << ' ';
	else visited_first = true;
	cout << tree.x;	
	if (tree.l) pre_order(*tree.l);
	if (tree.r) pre_order(*tree.r);
}

void post_order(const bst_node& tree) {
	if (tree.l) post_order(*tree.l);
	if (tree.r) post_order(*tree.r);
	if (visited_first) cout << ' ';
	else visited_first = true;
	cout << tree.x;
}

void in_order(const bst_node& tree) {
	if (tree.l) in_order(*tree.l);
	if (visited_first) cout << ' ';
	else visited_first = true;
	cout << tree.x;
	if (tree.r) in_order(*tree.r);
}

int main() {
	string s;
	bst_node* tree = nullptr;
	while (cin >> s) {
		if (s == "I") {
			int x; cin >> x; 
			add_tree(x, tree);
		} else if (s == "P") {
			int x; cin >> x;
			if (find_tree(x, tree)) cout << x << " existe" << endl;
			else cout << x << " nao existe" << endl;
		} else if (s == "R") {
			int x; cin >> x;
			remove_tree(x, tree);
		} else if (s == "INFIXA") {
			visited_first = false;
			in_order(*tree);
			cout << endl;
		} else if (s == "PREFIXA") {
			visited_first = false;
			pre_order(*tree);
			cout << endl;
		} else if (s == "POSFIXA") {
			visited_first = false;
			post_order(*tree);
			cout << endl;
		}
	}
}