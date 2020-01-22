/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
Note: A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
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
    std::vector<std::vector<int>> results;
    int S;

    void recurse1(const TreeNode* node, const int sum, std::vector<int>& stack) {
        const auto left = node->left;
        const auto right = node->right;
        const int new_sum = sum + node->val;
        
        stack.push_back(node->val);
        if (not left and not right) {
            if (new_sum == S) {
                results.push_back(stack);
            }
        } if (not right) {
            recurse1(left, new_sum, stack);
        } else if (not left) {
            recurse1(right, new_sum, stack);
        } else {
            recurse1(left, new_sum, stack);
            recurse1(right, new_sum, stack);
        }
        stack.pop_back();
    }     
    
	std::vector<std::vector<int>> solution1(TreeNode* root, const int sum) {
        if (not root) {
            return {};
        }

        results.clear();
        S = sum;
        auto stack = std::vector<int>();
        recurse1(root, 0, stack);
        
        return results;
	}
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
  		return solution1(root, sum);      
    }
};
