/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
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
    TreeNode* helper1(const std::vector<int>& nums, 
                        const size_t start, 
                        const size_t end) {
        if (start >= end) {
            return NULL;
        }

        const size_t mid = (start + end) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper1(nums, start, mid);
        root->right = helper1(nums, mid+1, end);

        return root;
    }

    TreeNode* solution1(std::vector<int>& nums) {
        /*
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(log(N))
         *
         * where N = size(nums) 
         *
         * */
        return helper1(nums, 0, nums.size());
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return solution1(nums); 
    }
};
