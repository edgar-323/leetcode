/*
Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.
In one move, we may choose two adjacent nodes and move one coin from one node to another.  (The move may be from parent to child, or from child to parent.)
Return the number of moves required to make every node have exactly one coin.

Example 1:
Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.

Example 2:
Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root [taking two moves].  Then, we move one coin from the root of the tree to the right child.

Example 3:
Input: [1,0,2]
Output: 2

Example 4:
Input: [1,0,0,null,3]
Output: 4

Note:
1<= N <= 100
0 <= node.val <= N
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
    int moves;
    int recurse1(TreeNode* node) {
        // This dfs() routine will return the status of the subtree rooted at node.
        // If it returns a positive number, then it returns a surplus which indicates that all those values must be moved upwards.
        // If it retruns a negative number, them it retruns a deficit which indicates that all those values must be moved downwards.
        // If it return 0, then the subtree rooted at node is coin-wise balanced at this point.
        // In either case all these values must be added to total moves.
        if (not node) {
            return 0;
        }
        const int left_need = recurse1(node->left);
        const int right_need = recurse1(node->right);
        moves += std::abs(left_need) + std::abs(right_need);
        return left_need + right_need + node->val - 1;
    }

    int solution1(TreeNode* root) {
        moves = 0;
        recurse1(root);
        return moves;
    }
public:
    int distributeCoins(TreeNode* root) {
  		return solution1(root);      
    }
};
