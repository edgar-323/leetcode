/*
Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1

Example 2: 
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7

Note: You may assume the tree (i.e., the given root node) is not NULL.
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
    int max_depth;
    int left_most_val;
    void recurse1(TreeNode* node, const int depth) {
        if (not node->left and not node->right and depth > max_depth) {
            max_depth = depth;
            left_most_val = node->val;
        }
        if (node->left) {
            recurse1(node->left, depth+1);
        }
        if (node->right) {
            recurse1(node->right, depth+1);
        }
    }
	int solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         *      Where   N = size(root)
         *              H = height(root)
         */
        max_depth = -1;
        left_most_val = INT_MIN;
        recurse1(root, 0);

        return left_most_val;
	}
public:
    int findBottomLeftValue(TreeNode* root) {
  		return solution1(root);      
    }
};
