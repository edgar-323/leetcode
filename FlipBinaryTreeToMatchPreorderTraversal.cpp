/*
Given a binary tree with N nodes, each node has a different value from {1, ..., N}.
A node in this binary tree can be flipped by swapping the left child and the right child of that node.
Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.
(Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)
Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.
If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.
If we cannot do so, then return the list [-1].

Example 1:
Input: root = [1,2], voyage = [2,1]
Output: [-1]

Example 2:
Input: root = [1,2,3], voyage = [1,3,2]
Output: [1]

Example 3:
Input: root = [1,2,3], voyage = [1,2,3]
Output: []

Note:
1 <= N <= 100
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
    int N;
     
    int failure(std::vector<int>& results) {
        results = std::vector<int>{-1};
        return -1;
    }

    int success(std::vector<int>& results, const std::vector<int>& temp, const int i) {
        results.insert(results.end(), temp.begin(), temp.end());
        return i;
    }

    int no_flip1(TreeNode* node, const int i, const std::vector<int>& voyage, std::vector<int>& results) {
        // Assumes node->val == voyage[i]
        auto temp = std::vector<int>();   
        auto j = recurse1(node->left, i+1, voyage, temp);
        if (j < 0) {
            results = std::vector<int>{-1};
            return -1;
        }
        j = recurse1(node->right, j, voyage, temp);
        if (j < 0) {
            results = std::vector<int>{-1};
            return -1;
        }

        return success(results, temp, j);
    }
    
    int flip1(TreeNode* node, const int i, const std::vector<int>& voyage, std::vector<int>& results) {
        // Assumes node->val == voyage[i]
        auto temp = std::vector<int>();
        auto j = recurse1(node->right, i+1, voyage, temp);
        if (j < 0) {
            return failure(results);
        }
        j = recurse1(node->left, j, voyage, temp);
        if (j < 0) {
            return failure(results);
        }
        results.push_back(node->val);

        return success(results, temp, j);
    }

    int recurse1(TreeNode* node, const int i, const std::vector<int>& voyage, std::vector<int>& results) {
        if (i == N) {
            if (node) {
                results = {-1};
                return -1;
            }
            return i;
        } else if (not node) {
            return i;
        } else if (node->val != voyage[i]) {
            results = {-1};
            return -1; 
        }
         
        auto no_flip = std::vector<int>();
        auto j = no_flip1(node, i, voyage, no_flip);
        if (j < 0) {
            return flip1(node, i, voyage, results);
        }
        auto flip = std::vector<int>();
        auto k = flip1(node, i, voyage, flip);
        if (k < 0) {
            return success(results, no_flip, j);
        }
         
        return no_flip.size() < flip.size() ? success(results, no_flip, j) : success(results, flip, k);
    }

    std::vector<int> solution1(TreeNode* root, const std::vector<int>& voyage) {
        N = voyage.size();
        auto results = std::vector<int>();
        recurse1(root, 0, voyage, results);

        return results;
    }
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        return solution1(root, voyage);    
    }
};
