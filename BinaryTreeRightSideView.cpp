/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
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
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = # of nodes
         */
        if (not root) {
            return {};
        }

        auto view = std::vector<int>();
        auto Q = std::queue<TreeNode*>();
        Q.push(root);

        while (not Q.empty()) {
            view.push_back(Q.front()->val);  
            for (size_t i = Q.size(); i; --i) {
                TreeNode* node = Q.front(); Q.pop();
                if (node->right) {
                    Q.push(node->right);
                }
                if (node->left) {
                    Q.push(node->left);
                }
            } 
        }

        return view; 
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        return solution1(root);       
    }
};
