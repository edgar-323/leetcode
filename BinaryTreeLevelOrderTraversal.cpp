/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:

[
  [3],
  [9,20],
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
class QueueNode {
private:
    TreeNode* node;
    size_t dist;
public: 
    QueueNode(TreeNode* node, size_t dist) {
        this->node = node;
        this->dist = dist;
    }
    
    TreeNode* getNode() {
        return this->node;
    }
    
    size_t getDist() {
        return this->dist;
    }
};

class Solution {
private:
    /**************************************************************/
    vector<vector<int>> solution1(TreeNode* root) {
        vector<vector<int>> levels;
        if (root == NULL) {
            return levels;
        }
        std::queue<QueueNode> Q;
        Q.push(QueueNode(root, 0));
        size_t dist;
        TreeNode* node;
        while (!Q.empty()) {
            node = Q.front().getNode();
            dist = Q.front().getDist();
            Q.pop();
            if (levels.size() <= dist) {
                levels.push_back(vector<int>());
            }
            levels[dist].push_back(node->val);
            if (node->left != NULL) {
                Q.push(QueueNode(node->left, dist+1));
            }
            if (node->right != NULL) {
                Q.push(QueueNode(node->right, dist+1));
            }
        }
        return levels;
    }
    /**************************************************************/
    typedef std::vector<int> Level;
    typedef std::vector<Level> Levels;
    Levels solution2(TreeNode* root) {
        /*
        Time-Complexity: 
            ==> O(N)
        Space-Complexity:
            ==> O(N / 2)
            ==> O(N)
        */
        Levels levels;
        if (root == NULL) {
            return levels;
        }
        std::queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty()) {
            Level level;
            for (size_t size = Q.size(); size > 0; --size) {
                TreeNode* node = Q.front(); Q.pop();
                level.push_back(node->val);
                if (node->left != NULL) {
                    Q.push(node->left);
                }
                if (node->right != NULL) {
                    Q.push(node->right);
                }
            }
            levels.push_back(level);
        }
        return levels;
    }
    /**************************************************************/ 
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        return solution2(root);
    }
};
