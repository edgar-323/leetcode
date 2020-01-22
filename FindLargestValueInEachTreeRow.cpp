/*
You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]
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
    std::vector<int> solution1(TreeNode* root) {
        if (not root) {
            return {};
        }
        auto max_vals = std::vector<int>();
        auto Q = std::queue<TreeNode*>();
        Q.push(root);

        while (not Q.empty()) {
            const int M = Q.size();
            int max_val = INT_MIN;
            for (int i = M; i; --i) {
                TreeNode* node = Q.front(); Q.pop();
                max_val = std::max(max_val, node->val);
                if (node->left) {
                    Q.push(node->left);
                }
                if (node->right) {
                    Q.push(node->right);
                }
            }
            max_vals.push_back(max_val);
        }

        return max_vals;
    }

public:
    vector<int> largestValues(TreeNode* root) {
        return solution1(root);        
    }
};
