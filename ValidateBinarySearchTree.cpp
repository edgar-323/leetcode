/*
Given a binary tree, determine if it is a valid binary search tree (BST).
Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
    2
   / \
  1   3
Input: [2,1,3]
Output: true

Example 2:
    5
   / \
  1   4
     / \
    3   6
Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
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
    long long toLL(int x) {
        return ((long long) x);
    }
    
    bool recurse1(TreeNode* node, long long min, long long max) {
        if (node == NULL) {
            return true;
        } else if (toLL(node->val) <= min || toLL(node->val) >= max) {
            return false;
        } else {
            return recurse1(node->left, min, node->val) and recurse1(node->right, node->val, max);
        }
    } 
    
    bool solution1(TreeNode* root) {
        return recurse1(root, LLONG_MIN, LLONG_MAX);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        return solution1(root);
    }
};
