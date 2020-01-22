/*
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.

Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]

Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]

Note:
The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.
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
	TreeNode* recurse1(TreeNode* node) {
        if (not node) {
            return NULL;
        }
        node->left = recurse1(node->left);
        node->right = recurse1(node->right);  
        return not node->val and not node->left and not node->right ? NULL : node;    
	}

	TreeNode* solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         *      Where N = size(root) and H = height(root)
         */ 
        return recurse1(root);
	}
public:
    TreeNode* pruneTree(TreeNode* root) {
  		return solution1(root);      
    }
};
