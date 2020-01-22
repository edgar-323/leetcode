/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.
Note: A leaf is a node with no children.

Example:
Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:
Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
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
    int recurse1(const TreeNode* node, const int suffix) {
        const auto left = node->left;
        const auto right = node->right;
        const auto new_suffix = 10*suffix + node->val;

        if (not left and not right) {
            return new_suffix;
        } else if (not right) {
            return recurse1(left, new_suffix);
        } else if (not left) {
            return recurse1(right, new_suffix);
        } else {
            return recurse1(left, new_suffix) + recurse1(right, new_suffix);
        }
    }

    int solution1(TreeNode* root) {
        return root ? recurse1(root, 0) : 0; 
    }
public:
    int sumNumbers(TreeNode* root) {
        return solution1(root);        
    }
};
