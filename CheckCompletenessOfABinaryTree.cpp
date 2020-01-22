/*
Given a binary tree, determine if it is a complete binary tree.
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example 1:
Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

Example 2:
Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.
 
Note:
The tree will have between 1 and 100 nodes.
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
    int N;
    int size(TreeNode* node) {
        if (not node) {
            return 0;
        }
        return 1 + size(node->left) + size(node->right);
    }
    
    void build_heap(TreeNode* node, const int i, std::vector<TreeNode*>& heap) {
        if (not node or i > N) {
           return;
        }
        heap[i] = node;
        build_heap(node->left, left_child(i), heap);
        build_heap(node->right, right_child(i), heap);
    } 
    
    int left_child(const int i) {
        return 2*i;
    }

    int right_child(const int i) {
        return 2*i + 1;
    }

    bool solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        N = size(root);
        auto heap = std::vector<TreeNode*>(N+1, NULL);
        build_heap(root, 1, heap);

        for (int i = 1; i <= N; ++i) {
            if (not heap[i]) {
                return false;
            }
        }

        return true;
    }
public:
    bool isCompleteTree(TreeNode* root) {
        return solution1(root);
    }
};
