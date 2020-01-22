/*
Given the root of a binary tree, each node in the tree has a distinct value.
After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
Return the roots of the trees in the remaining forest.  You may return the result in any order.

Example 1:
Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Constraints:
The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.
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
    void recurse1(TreeNode* node, const bool is_root, const std::unordered_set<int>& to_delete, std::vector<TreeNode*>& results) {
        if (not node) {
            return;
        }

        auto left = node->left;
        auto right = node->right;
     
        const bool delete_me = to_delete.count(node->val);

        if (not delete_me and is_root) {
            results.push_back(node);
        }
        if (left and to_delete.count(left->val)) {
            node->left = NULL;
            recurse1(left, false, to_delete, results); 
        } else {
            recurse1(left, delete_me, to_delete, results);
        }
        if (right and to_delete.count(right->val)) {
            node->right = NULL;
            recurse1(right, false, to_delete, results);
        } else {
            recurse1(right, delete_me, to_delete, results);
        }
    }
    std::vector<TreeNode*> solution1(TreeNode* root, std::vector<int>& to_delete) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where N = # of nodes in tree
         */
        if (not root) {
            return {};
        }
        auto results = std::vector<TreeNode*>(); 
        auto delete_set = std::unordered_set<int>(to_delete.begin(), to_delete.end());
        recurse1(root, not delete_set.count(root->val), delete_set, results);

        return results;
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        return solution1(root, to_delete);        
    }
};
