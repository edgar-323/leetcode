/*
Given a binary tree, we install cameras on the nodes of the tree.
Each camera at a node can monitor its parent, itself, and its immediate children.
Calculate the minimum number of cameras needed to monitor all nodes of the tree.

Example 1:
Input: [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.

Example 2:
Input: [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.

Note:
The number of nodes in the given tree will be in the range [1, 1000].
Every node has value 0.
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
    int*** cache1;
    void enumerate(TreeNode* node) {
        if (not node) {
            return;
        }
        node->val = N++;
        enumerate(node->left);
        enumerate(node->right);
    }
    void init_cache1(TreeNode* root) {
        N = 0;
        enumerate(root);
        cache1 = new int**[N];
        for (int i = 0; i < N; ++i) {
            cache1[i] = new int*[2];
            for (int j = 0; j < 2; ++j) {
                cache1[i][j] = new int[2];
                for (int k = 0; k < 2; ++k) {
                    cache1[i][j][k] = -1;
                }
            }
        }
    }
    void destroy_cache1() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 2; ++j) {
                delete[] cache1[i][j];
            }
            delete[] cache1[i];
        }
       delete[] cache1; 
    }
    int recurse1(TreeNode* node, const bool has_camera, const bool is_monitored) {
        if (not node) {
            return 0;
        } else if (cache1[node->val][has_camera][is_monitored] >= 0) {
            return cache1[node->val][has_camera][is_monitored];
        }

        int min_cameras;
        
        if (has_camera) {
            // This node has camera on it
            min_cameras = 1 + recurse1(node->left, false, true) + recurse1(node->right, false, true);
        } else if (is_monitored) {
            // This node is being monitored so it can choose to not place camera or to place it.
            min_cameras = std::min<int>(
                            {
                                recurse1(node->left, false, false) + recurse1(node->right, false, false), // No Camera Here
                                1 + recurse1(node->left, false, true) + recurse1(node->right, false, true) // Place Camera Here
                            });
        } else {
            // Lets decide if we should place camera at this node, or at left child, or at right child
            // Regardless where we place the camera, this node will be definitely monitored 
            // (which is what we care about at the end of the day)
            min_cameras = std::min<int>(
                            {
                                1 + recurse1(node->left, false, true) + recurse1(node->right, false, true), // Place Camera Here
                                node->left ? recurse1(node->left, true, false) + recurse1(node->right, false, false) : INT_MAX, // Camera on left child
                                node->right ? recurse1(node->left, false, false) + recurse1(node->right, true, false) : INT_MAX // Camera on right child
                            }); 
        }
        
        return cache1[node->val][has_camera][is_monitored] = min_cameras;
    }
    int solution1(TreeNode* root) {
        init_cache1(root);
        const int min_cameras = recurse1(root, false, false);
        destroy_cache1();

        return min_cameras;
    }
public:
    int minCameraCover(TreeNode* root) {
        return solution1(root);
    }
};
