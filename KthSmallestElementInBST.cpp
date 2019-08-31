/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Example 1:
Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
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
    int result;
    int k;
    void recurse1(TreeNode* node) {
        if (node == NULL) {
            return; 
        }
        
        recurse1( node->left );
        if (k <= 0) {
            return;
        } else if (k == 1) {
            result = node->val;
            --k;
            return;
        }
        --k;
        recurse1( node->right ); 
    }
    int solution1(TreeNode* root, int k) {
        /* 
         * Time-Complexity:     O( H )
         * Space-Complexity:    O( H )
         * where H = heght( root)
         * */
        k = _k;
        result = -1;
        recurse1( root );
        return result;        
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        return solution1( root, k );
    }
};
