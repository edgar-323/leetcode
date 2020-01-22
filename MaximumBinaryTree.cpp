/*
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:

Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:

The size of the given array will be in the range [1,1000].
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
    TreeNode* recurse1(const int start, const int end, const std::vector<int>& nums) {
        if (start >= end) {
            return NULL;
        }
        int i = start;
        for (int j = start+1; j < end; ++j) {
            if (nums[i] < nums[j]) {
                i = j;
            }
        }
        TreeNode* root = new TreeNode(nums[i]);
        root->left = recurse1(start, i, nums);
        root->right = recurse1(i+1, end, nums);
        
        return root;    
    }

    TreeNode* solution1(const std::vector<int>& nums) {
        return recurse1(0, nums.size(), nums);    
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return solution1(nums);        
    }
};
