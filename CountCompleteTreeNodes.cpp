/*
Given a complete binary tree, count the number of nodes.
Note:
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:
Input: 
    1
   / \
  2   3
 / \  /
4  5 6
Output: 6
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
    /*************************************************************************************/
    int height(TreeNode* node) {
        return node ? 1 + height(node->left) : -1;
    }
    
    int recurse1(TreeNode* node) {
        const int h = height(node);
        return  h < 0 ? 0 :
                h-1 == height(node->right) ?
                (1 << h)    + recurse1(node->right):
                (1 << h-1)  + recurse1(node->left);
    }

    int solution1(TreeNode* root) {
        return recurse1(root);
    }
    /*************************************************************************************/
    int depth(TreeNode* root) {
        int d = 0;
        while (root->left) {
            ++d;
            root = root->left;
        }
        return d;
    }

    bool node_exists(const int j, const int d, TreeNode* root) {
        int left = 0;
        int right = (1 << d) - 1;
        for (int i = 0; i < d; ++i) {
            const auto mid = left + (right - left)/2;
            if (j <= mid) {
                root = root->left;
                right = mid;
            } else {
                root = root->right;
                left = mid + 1;
            }
        }

        return root;
    }

    int solution2(TreeNode* root) {
        /* Time-Complexity:     O(d^2)
         * Space-Complexity:    O(1)
         *      Where:
         *          d = log(N)
         *          N = # of nodes
         */
        if (not root) {
            return 0;
        }
        const int d = depth(root);
        if (d == 0) {
            return 1;
        }
        int left = 0;
        int right = (1 << d) - 1;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (node_exists(mid, d, root)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // The tree contains 2**d - 1 nodes on the first (d - 1) levels
        // and left nodes on the last level.
        return left + (1 << d) - 1;
    }
    /*************************************************************************************/
public:
    int countNodes(TreeNode* root) {
        return solution1(root); 
    }
};
