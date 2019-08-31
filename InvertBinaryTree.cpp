/*
Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so f*** off.
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
    TreeNode* invert(TreeNode* node) {
        if (node == NULL) {
            return NULL;
        }
        
        TreeNode* newRight = invert(node->left);
        node->left = invert(node->right);
        node->right = newRight;
        return node;
    }
    
    TreeNode* solution1(TreeNode* root) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( H )
         *  where N = size( root ) and H = height( root )
         * */
        return invert( root );
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        return solution1(root);
    }
};
