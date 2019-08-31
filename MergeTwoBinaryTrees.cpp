/*
Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.
You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

Example1:
Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7


Note: The merging process must start from the root nodes of both trees.
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
    TreeNode* solution1(TreeNode* s, TreeNode* t) {
        /*
        Time-Complexity:    O(max{size(s),   size(t)})
        Space-Complexity:   O(max{height(s), height(t)})
        */
        
        if (s == NULL) {
            return t;
        } else if (t == NULL) {
            return s;
        }
        s->val += t->val;
        s->left = mySolution(s->left, t->left);
        s->right = mySolution(s->right, t->right);
        return s;
    }
    
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        return solution1( t1, t2 );
    }
};
