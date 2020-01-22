/*
We are given a binary tree (with root node root), a target node, and an integer value K.
Return a list of the values of all nodes that have a distance K from the target node.  
The answer can be returned in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
Output: [7,4,1]
Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.

Note:
The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.
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
    std::vector<int> results;
    TreeNode* target;
    int K;

    int bottom_up(TreeNode* node) {
        // If `target` is in the subtree rooted at `node`, then this function returns the distance between `target` and the caller of this function 
        // Otherwise, this function returns -1.
        if (not node) {
            return -1;
        } else if (node == target) {
            top_down(node->left, 1);
            top_down(node->right, 1);
            return 1;
        }

        const int left_dist = bottom_up(node->left);
        if (left_dist > 0) {
            // target is located in left subtree
            if (K - left_dist == 0) {
                results.push_back(node->val);
            } else if (K - left_dist > 0) {
                top_down(node->right, left_dist + 1);
            }
            return left_dist + 1;
        }
        const int right_dist = bottom_up(node->right);
        if (right_dist > 0) {
            // target is located in right subtree
            if (K - right_dist == 0) {
                results.push_back(node->val);
            } else if (K - right_dist > 0) {
                top_down(node->left, right_dist + 1);
            }
            return right_dist + 1;
        }
        // `target` not found in subtree rooted at `node`
        return -1;
    }

    void top_down(TreeNode* node, const int dist) {
        // `target` is either an ancestor of `node` or is the child of an ancestor of `node` and is at a distance of `dist` away from `node`.
        if (not node) {
           return;
        } 
        if (dist == K) {
           results.push_back(node->val);
        } else if (dist < K) { 
            top_down(node->left, dist + 1);
            top_down(node->right, dist + 1); 
        }
    }

    std::vector<int> solution1(TreeNode* root, TreeNode* target, const int K) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         *      Where:
         *          N = # of nodes
         *          H = tree height
         */
        if (not K) {
            // Only target is at a distance 0 from itself
            return { target->val };
        }
        this->target = target;
        this->K = K;
        results.clear();
        bottom_up(root); 
       
        return results; 
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        return solution1(root, target, K);        
    }
};
