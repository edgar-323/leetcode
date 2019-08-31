/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Note:
All of the nodes' values will be unique.
p and q are different and both values will exist in the binary tree.
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
    void getPath(TreeNode* node, TreeNode* target, std::deque<TreeNode*>& Q) {
        if (node == NULL) {
            return;
        }
        
        Q.push_back(node);
        
        if (node == target) {
            return;
        }
        
        getPath(node->left, target, Q);
        if (Q.back() == target) {
            return;
        }
        
        getPath(node->right, target, Q);
        if (Q.back() == target) {
            return;
        }
        
        Q.pop_back();
    }
    
    TreeNode* mySolution(TreeNode* root, TreeNode* p, TreeNode* q) {
        /*
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        */
        
        std::deque<TreeNode*> P;
        std::deque<TreeNode*> Q;
        getPath(root, p, P);
        getPath(root, q, Q);
        
        TreeNode* LCA = NULL;
        
        while (!P.empty() && !Q.empty() && P.front() == Q.front()) {
            LCA = P.front();
            P.pop_front();
            Q.pop_front();
        }
        
        return LCA;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return mySolution(root, p, q);
    }
};
