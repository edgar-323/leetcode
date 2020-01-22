/*
Given inorder and postorder traversal of a tree, construct the binary tree.
Note:
You may assume that duplicates do not exist in the tree.

For example, given
inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
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
    TreeNode* recurse1(
                const int i1, 
                const int j1, 
                const int i2, 
                const int j2, 
                const std::vector<int>& inorder, 
                const std::vector<int>& postorder) {
        // (i1, j1) are inclusive slices of inorder
        // (i2, j2) are inclusive slices of postorder
        // Assumes (j1 - i1) == (j2 - i2)
        // the root will be at postorder[j2] (remember postorder outputs left, right, and root last)
        if (i1 > j1) {
            return NULL;
        } 
        if (i1 == j1) {
            // assumes inorder[i1] == postorder[i2]
            return new TreeNode(inorder[i1]);
        }
        auto root = new TreeNode(postorder[j2]);
        
        int root_pos;
        for (root_pos = j1; root_pos >= i1 and inorder[root_pos] != root->val; --root_pos);
        const int num_left = root_pos - i1;
        const int num_right = j1 - root_pos;

        root->left = recurse1(i1, i1 + (num_left - 1), i2, i2 + (num_left - 1), inorder, postorder);
        root->right = recurse1(root_pos + 1, root_pos + 1 + (num_right - 1), i2 + num_left, i2 + num_left + (num_right - 1), inorder, postorder);

        return root;
    }

    TreeNode* solution1(std::vector<int>& inorder, std::vector<int>& postorder) {
        return recurse1(0, inorder.size()-1, 0, postorder.size()-1, inorder, postorder);
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return solution1(inorder, postorder);    
    }
};
