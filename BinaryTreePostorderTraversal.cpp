/*
Given a binary tree, return the postorder traversal of its nodes' values.

Example:
Input: [1,null,2,3]
   1
    \
     2
    /
   3
Output: [3,2,1]

Follow up: Recursive solution is trivial, could you do it iteratively?
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
    void recurse1(TreeNode* node, std::vector<int>& postorder) {
        if (not node) {
            return;
        }
        recurse1(node->left, postorder);
        recurse1(node->right, postorder);
        postorder.push_back(node->val);
    }

    std::vector<int> solution1(TreeNode* root) {
        // Recursive
        auto postorder = std::vector<int>();  
        recurse1(root, postorder);

        return postorder;
    }

    std::vector<int> solution2(TreeNode* root) {
        auto postorder = std::vector<int>();
        auto stack = std::stack<TreeNode*>();
        if (root) {
            stack.push(root);
        }
        
        while (not stack.empty()) {
            auto node = stack.top();
            if (node->left) {
                auto left = node->left;
                node->left = NULL;
                stack.push(left);
            } else if (node->right) {
                auto right = node->right;
                node->right = NULL;
                stack.push(right);
            } else {
                postorder.push_back(node->val);
                stack.pop();
            }
        }

        return postorder;
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        return solution2(root);
    }
};
