/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
 

But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3
 

Note:
Bonus points if you could solve it both recursively and iteratively.
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
    bool equal(TreeNode* node1, TreeNode* node2) {
        if (node1 == NULL || node2 == NULL) {
            return node1 == NULL && node2 == NULL;
        }
        return node1->val == node2->val;
    }
    
    bool verify(TreeNode* node1, TreeNode* node2) {
        if (node1 == NULL || node2 == NULL) {
            return equal(node1, node2);
        }
        return equal(node1, node2) && 
                verify(node1->left, node2->right) && 
                verify(node1->right, node2->left);
    }
    
    bool solution1(TreeNode* root) {
        /*
        ***************************************************************
        It took me a while to realzie how easy this problem was.
        I was trying to solve it by collecting an InOrder-Traversal
        of the left subtree of root, and comparing the collection 
        with a PostOrder-Traversal of the right subtree.
        With a little analysis, it can be shown that this fails.
        My next move was going to be to collect LevelOrder-Traversals 
        of the Left and Right subtrees and reverse comparing them.
        This would have certainly worked, however, the LevelOrder 
        concept allowed me to realize this simpler (and equivalent) 
        method.
        ***************************************************************
        Time-Complexity: 
            ==> O(N)
        Space-Complexity: 
            ==> O(H) 
            ==> O(N) 
        Where H = height(root).
        ***************************************************************
        */
        return (root == NULL) ? true : verify(root->left, root->right);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return solution1(root);
    }
};
