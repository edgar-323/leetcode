/*
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private: 
    /***********************************************************/
    bool isSubTree;
    TreeNode* t;
    int T;
    /***********************************************************/
    int height(TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        return 1 + max(height(node->left), height(node->right));
    }
    
    bool equal(const TreeNode* s, const TreeNode* t) {
        if (s == NULL) {
            return t == NULL;
        } else if (t == NULL) {
            return false;
        }
        return (s->val == t->val) && 
                equal(s->left, t->left) && 
                equal(s->right, t->right);
    }
    
    void checkParameters(const TreeNode* s, const int S) {
        // before checking tree equality, both trees must have same # of nodes
        if (S == T && !isSubTree && equal(s, t)) {
            isSubTree = true;
        }
    }
    
    int recurse1(const TreeNode* s) {
        // This returns the size of `s`
        if (s == NULL) {
            return 0;
        }
        const int S = 1 + std::max(recurse1(s->left), recurse1(s->right));
        // checks whether `s` might be equal to `t`
        checkParameters(s, S);
        return S;
    }
    
    bool solution1(const TreeNode* s, TreeNode* t0) {
        /*
        Time-Complexity:    O(size(s) + size(t))
        Space-Complexity:   O(height(s) + height(t))
        */
        // `t` and `T` are global variables. 
		t = t0;
        T = height(t);
        if (T == 0) {
            return s == NULL;
        }
        isSubTree = false;
        recurse1(s);
        return isSubTree;
    }
    /***********************************************************/
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return solution1(s, t);
    }
};
