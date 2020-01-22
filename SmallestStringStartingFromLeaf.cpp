/*
Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.
Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
(As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)

Example 1:
Input: [0,1,2,3,4,3,4]
Output: "dba"

Example 2:
Input: [25,1,3,1,3,0,2]
Output: "adz"

Example 3:
Input: [2,2,1,null,1,0,null,0]
Output: "abc"

Note:
The number of nodes in the given tree will be between 1 and 8500.
Each node in the tree will have a value between 0 and 25.
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
    std::string letter(const int x) {
        return std::string(1, char(x + 'a'));
    }

    std::string recurse1(const TreeNode* node, const std::string& suffix) {
        const auto left = node->left;
        const auto right = node->right;
        const auto new_suffix = letter(node->val) + suffix;

        if (not left and not right) {
            return new_suffix;
        } else if (not right) {
            return recurse1(left, new_suffix); 
        } else if (not left) {
            return recurse1(right, new_suffix); 
        } else {
            return std::min(recurse1(left, new_suffix), recurse1(right, new_suffix));
        }
    }

    std::string solution1(TreeNode* root) {
        return root ? recurse1(root, "") : ""; 
    }
public:
    string smallestFromLeaf(TreeNode* root) {
        return solution1(root);    
    }
};
