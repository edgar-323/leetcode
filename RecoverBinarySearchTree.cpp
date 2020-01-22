/*
Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

Example 1:
Input: [1,3,null,null,2]
   1
  /
 3
  \
   2
Output: [3,1,null,null,2]
   3
  /
 1
  \
   2

Example 2:
Input: [3,1,4,null,null,2]
  3
 / \
1   4
   /
  2
Output: [2,1,4,null,null,3]
  2
 / \
1   4
   /
  3

Follow up:
A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
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
    /*********************************************************************************************/
    void recurse1(TreeNode* node, std::vector<TreeNode*>& inorder) {
        if (not node) {
            return;
        }
        recurse1(node->left, inorder);
        inorder.push_back(node);
        recurse1(node->right, inorder);
    }
    void solution1(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
        auto inorder = std::vector<TreeNode*>();
        recurse1(root, inorder);
        const int N = inorder.size();
        TreeNode* x = nullptr;
        TreeNode* y = nullptr;
        for (int i = 0; i < N-1; ++i) {
            if (inorder[i]->val > inorder[i+1]->val) {
                y = inorder[i+1];
                if (not x) {
                    x = inorder[i];
                }
            }
        }
        std::swap(x->val, y->val);
    }
    /*********************************************************************************************/
    void solution2(TreeNode* root) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(H)
         */
        auto stack = std::stack<TreeNode*>();
        TreeNode* x = nullptr;
        TreeNode* y = nullptr;
        TreeNode* pred = nullptr;
        while (root or not stack.empty()) {
            while (root) {
                stack.push(root);
                root = root->left;
            }
            root = stack.top(); stack.pop();
            if (pred and pred->val > root->val) {
                y = root;
                if (not x) {
                    x = pred;
                }
            }
            pred = root;
            root = root->right;
        }
        std::swap(x->val, y->val);
    }
    /*********************************************************************************************/
    void solution3(TreeNode* root) {
        TreeNode* x = nullptr;
        TreeNode* y = nullptr;
        TreeNode* pred = nullptr;
        TreeNode* predecessor = nullptr;

        while (root) {
            if (root->left) {
                predecessor = root->left;
                while (predecessor->right and predecessor->right != root) {
                    predecessor = predecessor->right;
                }
                if (predecessor->right) {
                    predecessor->right = root;
                    root = root->left;
                } else {
                    if (pred and pred->val > root->val) {
                        y = root;
                        if (not x) {
                            x = pred;
                        }
                    }
                    pred = root;
                    root = root->right;
                }
            } else {
                if (pred and pred->val > root->val) {
                    y = root;
                    if (not x) {
                        x = pred;
                    }
                }
                pred = root;
                root = root->right;
            }
        }

        std::swap(x->val, y->val);
    }
    /*********************************************************************************************/
public:
    void recoverTree(TreeNode* root) {
        return solution3(root);
    }
};
