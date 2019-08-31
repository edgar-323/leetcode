/*
Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:
Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
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
    int recurse(TreeNode* node, int top) {
        if (node == NULL) {
            return top;
        }
        node->val += recurse(node->right, top);
        return recurse(node->left, node->val);
    }
    
    TreeNode* solution1(TreeNode* root) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(H)
            Where: 
                N = size(root)
                H = height(root)
        */
        recurse(root, 0);
        return root;
    }
    
public:
    TreeNode* convertBST(TreeNode* root) {
        return solution1(root);
    }
};
