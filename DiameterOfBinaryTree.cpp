/*
Given a binary tree, you need to compute the length of the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.

Example:
Given a binary tree 

          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: 
The length of path between two nodes is represented by the number of edges between them.
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
    int maxNodesInPath;
    
    int recurse1(const TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        
        // Compute maximum node-path in left subtree:
        const int left = recurse1(node->left);
        // Compute maximum node-path in right subtree:
        const int right = recurse1(node->right);
        
        // Check if max node-path on left combined with `node` and max node-path on right is bigger
        // than global max node-path of entire tree and, if so, update `maxNodesInPath`.
        maxNodesInPath = std::max(maxNodesInPath, 1 + left + right);
       
        // We return the max-node path of tree rooted at `node` but in doing so we return only the 
        // max node-path when we combine `node` with either `node->left` or `node->right` (but not both).
        // The reason we do this is so that callers at higher call stack can combine their value with `recurse1( node )`.
        // If we combine (`node`, `left`, `right`) then higher callers cannot combine this return value because a path 
        // cannot "split" by definition.
        // `maxNodesInPath` computes value when we combine (`node`, `left`, `right`).
		return 1 + std::max(left, right);
    }
    
    int solution1(TreeNode* root) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(H)
            Where:
                N = size(root)
                H = height(root)
        */
        
        // Reset `maxNodesInPath` 
        maxNodesInPath = 0;
        // Compute `maxNodesInPath` 
        recurse1(root);
        // Remeber that in a path of `maxNodesInPath` nodes, there are `maxNodesInPath - 1` edges.
        const int maxEdgesInPath = maxNodesInPath - 1;
        // If `root` was NULL, `maxEdgesInPath` will be negative,
        // so we make sure to return max{ `maxEdgesInPath`, 0 }.
        return std::max( maxEdgesInPath, 0 );
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return solution1(root);
    }
};
