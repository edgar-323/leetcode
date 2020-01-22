/*
Return the root node of a binary search tree that matches the given preorder traversal.
Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  
Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.

Example 1:
Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Note: 
1 <= preorder.length <= 100
The values of preorder are distinct.
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
    int i;
    TreeNode* recurse1(const int min_val, const int max_val, const std::vector<int>& preorder) {
        if (i >= N) {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[i++]);
        if (i == N or preorder[i] < min_val or preorder[i] > max_val) {
            return root;
        }
        if (preorder[i] < root->val) {
            root->left = recurse1(min_val, root->val, preorder);
            if (i < N and root->val < preorder[i] and preorder[i] < max_val) {
                root->right = recurse1(root->val, max_val, preorder);
            }
        } else {
            root->right = recurse1(root->val, max_val, preorder);
            if (i < N and min_val < preorder[i] and preorder[i] < root->val) {
                root->left = recurse1(min_val, root->val, preorder);
            }
        }

        return root;   
    }

	TreeNode* solution1(const std::vector<int>& preorder) {
        N = preorder.size();
        i = 0;
        return recurse1(INT_MIN, INT_MAX, preorder);
	}
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
  		return solution1(preorder);      
    }
};
