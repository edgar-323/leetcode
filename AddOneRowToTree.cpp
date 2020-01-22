/*
Given the root of a binary tree, then value v and depth d, you need to add a row of nodes with value v at the given depth d. The root node is at depth 1.
The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1, create two tree nodes with value v as N's left subtree root and right subtree root. And N's original left subtree should be the left subtree of the new left subtree root, its original right subtree should be the right subtree of the new right subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a tree node with value v as the new root of the whole original tree, and the original tree is the new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1

Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.
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
    int v;
    int d;
    
    void recurse1(TreeNode* node, const int depth) {
        if (not node) {
            return;
        } else if (depth == d-1) {
            auto left = new TreeNode(v);
            auto right = new TreeNode(v);
            
            left->left = node->left;
            right->right = node->right;
            
            node->left = left;
            node->right = right;      
        } else {
            recurse1(node->left, depth+1);
            recurse1(node->right, depth+1);
        }
    }

    TreeNode* solution1(TreeNode* root, const int v, const int d) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         */
        if (d == 1) {
            auto new_root = new TreeNode(v);
            new_root->left = root;
            return new_root;
        }
        this->v = v;
        this->d = d;
        recurse1(root, 1);

        return root;
    }

public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        return solution1(root, v, d);        
    }
};
