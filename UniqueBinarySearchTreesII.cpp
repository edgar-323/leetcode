/*
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
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
    typedef TreeNode* Tree;
    typedef std::vector<Tree> Trees;

    Trees recurse1(const int begin, const int end) {
        if (begin >= end) {
            return { NULL };
        }

        Trees trees;

        for (int i = begin; i < end; ++i) {
            for (Tree left_tree : recurse1(begin, i)) {
                for (Tree right_tree : recurse1(i+1, end)) {
                    Tree tree   = new TreeNode(i);
                    tree->left  = left_tree;
                    tree->right = right_tree;
                    trees.push_back(tree);
                }
            }
        }

        return trees;
    }

    Trees solution1(const int N) {
        /* Time-Complexity:
         *      T[N] = ∑ { T[i] * T[N-i] | i € {1,...,N} }
         * Space-Complexity:
         *      O(C(N))
         *      where C(N) = Catalan number of size N 
         * I don't know how to solve the equation for the runtime complexity (in order to express it analytically).
         * As for the spacetime complexity, the containers (vectors) we use to allocate the tree nodes never
         * exceeds the size of the output so the number of nodes held by the containers is O(C(N)).
         * Furthermore our recursion stack never goes deeper than N (since N is max height of any produced tree)
         * and we know C(N) >= N and thus we get O(C(N)) space complexity;.
         * */
        if (N < 1) {
            return { }; 
        }
        return recurse1(1, N+1);    
    }
public:
    std::vector<TreeNode*> generateTrees(int n) {
        return solution1(n);    
    }
};
