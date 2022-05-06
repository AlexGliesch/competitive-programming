/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right)
 * {}
 * };
 */
class Solution {
public:
  Node* expTreeRec(const string& s, int i, int j) { // [i, j)
    assert(j > i);
    if (j - i == 1) {
      assert(s[i] >= '0' && s[i] <= '9');
      return new Node(s[i]);
    }
    // remove paren around
    while (s[i] == '(' && s[j - 1] == ')') {
      int paren = 0;
      for (int k = i + 1; k < j - 1; ++k) {
        if (s[k] == '(')
          ++paren;
        else if (s[k] == ')') {
          --paren;
          if (paren < 0) break;
        }
      }
      if (paren == 0)
        ++i, --j; // stays well-formed after removing 1st and last
      else
        break;
    }
    // find operator to split on
    // can only split on operators outside parenthesis
    // split first on +-*/
    int paren = 0;
    int oplus = -1, ominus = -1, omul = -1, odiv = -1;
    for (int k = i; k < j; ++k) {
      if (s[k] == '(')
        ++paren;
      else if (s[k] == ')')
        --paren;
      else if (paren == 0) {
        if (s[k] == '+')
          oplus = k;
        else if (s[k] == '-')
          ominus = k;
        else if (s[k] == '*')
          omul = k;
        else if (s[k] == '/')
          odiv = k;
      }
    }
    int op = oplus != -1 ? oplus
                         : (ominus != -1 ? ominus : (omul != -1 ? omul : odiv));
    assert(op != -1);
    // cout << s[op] << endl;
    return new Node(s[op], expTreeRec(s, i, op), expTreeRec(s, op + 1, j));
  }

  Node* expTree(string s) { return expTreeRec(s, 0, s.size()); }
};