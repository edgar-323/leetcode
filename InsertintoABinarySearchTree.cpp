/*
Given the root node of a binary search tree (BST) and a value to be inserted into the tree, insert the value into the BST. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

Note that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3
And the value to insert: 5
You can return this binary search tree:

         4
       /   \
      2     7
     / \   /
    1   3 5
This tree is also valid:

         5
       /   \
      2     7
     / \   
    1   3
         \
          4
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
    void recurse1(TreeNode* node, const int val) {
        if (val < node->val) {
            if (not node->left) {
                node->left = new TreeNode(val);
            } else {
                recurse1(node->left, val);
            }
        } else {
            if (not node->right) {
                node->right = new TreeNode(val);
            } else {
                recurse1(node->right, val);
            }
        }
    }

    TreeNode* solution1(TreeNode* root, const int val) {
        /* Time-Complexity:     O(H)
         * Space-Complexity:    O(H)
         *      where H = height(root)
         */
        if (not root) {
            return new TreeNode(val);
        }
        recurse1(root, val);
        return root;        
    }

    TreeNode* solution2(TreeNode* root, const int val) {
        /* Time-Complexity:     O(H)
         * Space-Complexity:    O(1)
         *      where H = height(root)
         */
        if (not root) {
            return new TreeNode(val);
        }
        TreeNode* node = root;
        while (1) {
            if (val < node->val) {
                if (not node->left) {
                    node->left = new TreeNode(val);
                    return root;
                } else {
                    node = node->left;
                } 
            } else {
                if (not node->right) {
                    node->right = new TreeNode(val);
                    return root;
                } else {
                    node = node->right;
                }
            }
        }
    }
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        return solution2(root, val);
    }
};
