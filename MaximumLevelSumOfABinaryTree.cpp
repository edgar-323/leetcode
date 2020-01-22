/*
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
Return the smallest level X such that the sum of all the values of nodes at level X is maximal.

Example 1:
Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Note:
The number of nodes in the given tree is between 1 and 10^4.
-10^5 <= node.val <= 10^5
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
    int solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        if (not root) {
            return 0;
        } 

        auto Q = std::queue<TreeNode*>();
        Q.push(root);

        int max_sum = INT_MIN;
        int min_level = 0;
        
        int level = 0;
        while (not Q.empty()) {
            ++level;
            int sum = 0;   
            for (int i = Q.size(); i; --i) {
                TreeNode* node = Q.front(); Q.pop();
                sum += node->val; 
                if (node->left) {
                    Q.push(node->left);
                }
                if (node->right) {
                    Q.push(node->right);
                }
            }
            if (sum > max_sum) {
                min_level = level;
                max_sum = sum;
            }
        }

        return min_level;
    }
public:
    int maxLevelSum(TreeNode* root) {
        return solution1(root);
    }
};
