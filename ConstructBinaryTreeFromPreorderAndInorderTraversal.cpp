/*
Given preorder and inorder traversal of a tree, construct the binary tree.
Note: You may assume that duplicates do not exist in the tree.

For example, given
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
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
    size_t N;

    TreeNode* buildTree(
                const std::vector<int>& preOrder, 
                const std::vector<int>& inOrder, 
                size_t& i, 
                size_t& j, 
                std::unordered_set<int>& seen) {

        TreeNode* root = new TreeNode(preOrder[i]);

        std::stack<TreeNode*> stack;
        stack.push(root);
        
        seen.emplace(preOrder[i]);
        
        size_t start = i;
        while (preOrder[i] != inOrder[j]) {
            ++i;
        }
        ++i;
        ++j;
        for (int k = start+1; k < i; ++k) {
            stack.top()->left = new TreeNode(preOrder[k]);
            stack.push(stack.top()->left);
            seen.emplace(preOrder[k]);
        }
        TreeNode* last;
        while (!stack.empty()) {
            last = stack.top(); stack.pop();
            if (j < N) {
                if (seen.count( inOrder[j] )) {
                    j++;
                } else {
                    last->right = buildTree( preOrder, inOrder, i, j, seen );
                }
            }
        }
        return root;
    }
    
    TreeNode* solution1(const vector<int>& preOrder, const vector<int>& inOrder) {
        /*
        ***************************************************************
        ASSUMPTIONS:
        (1) size(preorder) == size(inorder)
        (2) For all i,j € {0,..,N-1}
            we have preorder[i] == preorder[j] 
            if and only if i == j.
            Similarly for inorder.
            This asserts uniqueness of elements.
        (3) For all i € {0,..,N-1}
            preorder[i] is in the set 
            {inorder[0], ..., inorder[N-1]}.
            Similarly for inorder.
            This ensures that they are traversals
            of the same tree, among other things.
        ***************************************************************
        EXPLANATION:
        Read the code faggot.
        ***************************************************************
        Time-Complexity: O(N)
        Space-Complexity: O(N)
        ***************************************************************
        */
        N = preOrder.size();
        if (N == 0) {
            return NULL;
        }
        size_t i = 0;
        size_t j = 0;
        std::unordered_set<int> seen;
        return buildTree( preOrder, inOrder, i, j, seen );
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return solution1(preorder, inorder);
    }
};
