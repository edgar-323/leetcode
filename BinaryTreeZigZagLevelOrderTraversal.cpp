/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
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
    typedef std::vector<int> Level;
    typedef std::vector<Level> Levels;

    Levels solution1(TreeNode* root) {
        /*
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *
         * where N = size(root)
         *
         * */
        Levels levels; 
        if (!root) {
            return levels;
        }
         
        std::queue<TreeNode*> Q;
        Q.push(root);
        bool reverse = false;     

        while (!Q.empty()) {
            Level level;
            for (size_t size = Q.size(); size > 0; --size) {
                TreeNode* node = Q.front(); Q.pop();
                level.push_back(node->val);
                if (node->left) {
                    Q.push(node->left);
                }
                if (node->right) {
                    Q.push(node->right);
                }
            }
             
            if (reverse) {
                std::reverse(level.begin(), level.end());
            }
            reverse = !reverse;
            levels.push_back(level);
        }

        return levels;
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        return solution1( root );
    }
};
