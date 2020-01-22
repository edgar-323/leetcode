/*
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
Basically, the deletion can be divided into two stages:
Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:
root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7
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
    TreeNode* sink_right(TreeNode* node, TreeNode* right) {
        if (not node->right) {
            node->right = right;
        } else {
            node->right = sink_right(node->right, right);
        }
        return node;
    }

    TreeNode* recurse1(TreeNode* node, const int key) {
        if (not node) {
            return NULL;
        }
        
        if (node->val == key) {
            // found the node
            if (not node->left and not node->right) {
                return NULL;
            } else if (not node->right) {
                return node->left;
            } else if (not node->left) {
                return node->right;
            } else {
                return sink_right(node->left, node->right); 
            }
        }

        node->left = recurse1(node->left, key);
        node->right = recurse1(node->right, key);

        return node;
    }

    TreeNode* solution1(TreeNode* root, int key) {
        return recurse1(root, key);
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        return solution1(root, key);        
    }
};
