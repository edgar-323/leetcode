/*
Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.
(A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)

Example 1:
Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation: 
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

Note:
The number of nodes in the tree is between 2 and 5000.
Each node will have value between 0 and 100000.
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
    int max_diff;
    std::pair<int,int> recurse1(TreeNode* node) {
        auto left = node->left;
        auto right = node->right;
        auto val = node->val;
        if (not left and not right) {
            return std::make_pair(val, val);
        } else if (not left) {
            auto right_pair = recurse1(right);
            max_diff = std::max<int>({max_diff, std::abs(val - right_pair.first), std::abs(val - right_pair.second)});
            return std::make_pair(std::min<int>({val, right_pair.first}), std::max<int>({val, right_pair.second}));
        } else if (not right) {
            auto left_pair = recurse1(left);
            max_diff = std::max<int>({max_diff, std::abs(val - left_pair.first), std::abs(val - left_pair.second)});
            return std::make_pair(std::min<int>({val, left_pair.first}), std::max<int>({val, left_pair.second}));
        } else {
            auto left_pair = recurse1(left);
            auto right_pair = recurse1(right);
            max_diff = std::max<int>({max_diff, std::abs(val - left_pair.first), std::abs(val - left_pair.second), std::abs(val - right_pair.first), std::abs(val - right_pair.second)});
            return std::make_pair(std::min<int>({val, left_pair.first, right_pair.first}), std::max<int>({val, left_pair.second, right_pair.second}));
        }
    }
	int solution1(TreeNode* root) {
        max_diff = 0;
        recurse1(root);
        return max_diff;
	}
public:
    int maxAncestorDiff(TreeNode* root) {
 		return solution1(root);       
    }
};
