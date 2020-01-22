/*
A full binary tree is a binary tree where each node has exactly 0 or 2 children.
Return a list of all possible full binary trees with N nodes.
Each element of the answer is the root node of one possible tree.
Each node of each tree in the answer must have node.val = 0.
You may return the final list of trees in any order.

Example 1:
Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:

Note:
1 <= N <= 20
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
    std::vector<TreeNode*> recurse1(const int N) {
        if (N == 1) {
            return { new TreeNode(0) };
        }
        auto results = std::vector<TreeNode*>();
        for (int n = 1; n < N; n += 2) {
            for (const auto& left : recurse1(n)) {
                for (const auto& right : recurse1(N - 1 - n)) {
                    auto root = new TreeNode(0);
                    root->left = left;
                    root->right = right;
                    results.push_back(root);
                }
            }
        }

        return results;
    }

	std::vector<TreeNode*> solution1(const int N) {
        return recurse1(N);
	}
public:
    vector<TreeNode*> allPossibleFBT(int N) {
  		return solution1(N);
    }
};
