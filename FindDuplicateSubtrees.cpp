/*
Given a binary tree, return all duplicate subtrees. 
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with same node values.

Example 1:
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
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
    std::unordered_set<std::string> seen;
    std::unordered_set<std::string> added;
    std::vector<TreeNode*> results;

    std::string recurse1(TreeNode* node) {
        auto subtree = std::to_string(node->val);
        if (node->left) {
            subtree = recurse1(node->left) + "," + subtree;
        } else {
            subtree = std::string("L") + "," + subtree;
        }
        if (node->right) {
            subtree = subtree + "," + recurse1(node->right);
        } else {
            subtree = subtree + "," + "R";
        }
        if (seen.count(subtree)) {
            if (not added.count(subtree)) {
                results.push_back(node);
                added.insert(subtree);
            }
        } else {
            seen.insert(subtree);
        }

        return subtree;
    }

    std::vector<TreeNode*> solution1(TreeNode* root) {
        if (not root) {
            return {};
        }

        seen.clear();
        added.clear();
        results.clear();

        recurse1(root);

        return results; 
    }

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        return solution1(root);    
    }
};
