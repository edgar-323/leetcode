/*
Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
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
    std::unordered_map<int, int> frequencies;

    int compute_frequencies(TreeNode* node) {
        if (not node) {
            return 0;
        }

        const int sum = node->val + compute_frequencies(node->left) + compute_frequencies(node->right);
        frequencies[sum]++; 
        
        return sum;
    }
         
	std::vector<int> solution1(TreeNode* root) {
        frequencies.clear();
        compute_frequencies(root);

        auto max_frequencies = std::vector<int>();
        int max_frequency = 0;
        for (auto cit = frequencies.cbegin(); cit != frequencies.cend(); ++cit) {
            const int sum = cit->first;
            const int frequency = cit->second;
            if (frequency > max_frequency) {
                max_frequencies = std::vector<int>{ sum };
                max_frequency = frequency;
            } else if (frequency == max_frequency) {
                max_frequencies.push_back(sum);
            }
        }

        return max_frequencies;
	}
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
  		return solution1(root);      
    }
};
