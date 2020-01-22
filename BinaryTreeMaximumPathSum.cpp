/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class NodeSum {
public:
    int include;
    int exclude;
    NodeSum() {
        include = exclude = 0;
    }
};

class Solution {
private:
    NodeSum getSum(TreeNode* node) {
        NodeSum mid = NodeSum();
        if (not node->left and node->right) {
            mid.include = mid.exclude = node->val;
        } else if (not node->left) {
            NodeSum right = getSum(node->right);
            mid.include = max<int>(
                            {
                                node->val, 
                                node->val + right.include
                            });
            mid.exclude = max<int>(
                            {
                                right.include, 
                                right.exclude
                             });
        } else if (not node->right) {
            NodeSum left = getSum(node->left);
            mid.include = max<int>(
                            {
                                node->val, 
                                node->val + left.include
                            });
            mid.exclude = max<int>(
                            {
                                left.include, 
                                left.exclude
                            });
        } else {
            NodeSum left = getSum(node->left);
            NodeSum right = getSum(node->right);
            mid.include = max<int>(
                            {
                                node->val, 
                                node->val + left.include, 
                                node->val + right.include
                            });
            mid.exclude = max<int>(
                            {
                                left.include, 
                                left.exclude, 
                                right.include, 
                                right.exclude, 
                                node->val + left.include + right.include
                            });
        }
        
        return mid;
    }
    
    int mySolution(TreeNode* root) {
        /*
        *******************************************************
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        *******************************************************
        */
        NodeSum nodeSum = getSum(root);
        return max(nodeSum.include, nodeSum.exclude);
    }
    
public:
    int maxPathSum(TreeNode* root) {
        return mySolution(root);
    }
};
