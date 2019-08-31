/*
Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]

Follow up: Recursive solution is trivial, could you do it iteratively?
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
    void inorderCollect(TreeNode* node, vector<int>& array) {
        if (node == NULL) {
            return;
        }
        inorderCollect(node->left, array);
        array.push_back(node->val);
        inorderCollect(node->right, array);
    }
    
    vector<int> solution1(TreeNode* root) {
        vector<int> results;
        inorderCollect(root, results);
        return results;
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        return solution1(root);
    }
};
