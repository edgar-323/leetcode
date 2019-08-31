/*
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
The same repeated number may be chosen from candidates unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]

Example 2:
Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
*/

class Solution {
private:
    /*************************************************************/
    void recurse1(vector<int>& nums, const int N,  int pos, 
             vector<int>& combo, vector<vector<int>>& results, 
             int target) {
        if (target == 0) {
            vector<int> combo2(combo);
            results.push_back(combo2);
        } else if (pos < N && target > 0) {
            int val = nums[pos];
            ++pos;
            recurse1(nums, N, pos, combo, results, target);
            vector<int> combo3 = vector(combo);
            while (target >= 0) {
                target -= val;
                combo3 = vector(combo3);
                combo3.push_back(val);
                recurse1(nums, N, pos, combo3, results, target);
            }
        }
    }
    vector<vector<int>> solution1(vector<int>& nums, int target) {
        /* MY SOLUTION */
        vector<vector<int>> results;
        vector<int> empty;
        recurse1(nums, nums.size(), 0, empty, results, target);
        return results;
    }
    /*************************************************************/
    void backtrack(std::vector<int>& nums, const int N, const int pos, 
                    std::vector<int>& combo, std::vector<std::vector<int>>& results, 
                    const int target) {
        if (target == 0) {
            results.push_back(vector(combo));
        } else if (target > 0) {
            for (int i = pos; i < N; ++i) {
                combo.push_back(nums[i]);
                backtrack(nums, N, i, combo, results, target-nums[i]);
                combo.pop_back();
            }
        }
    }
    vector<vector<int>> solution2(vector<int>& nums, int target) {
        /* SOLUTION FROM: 
            https://leetcode.com/problems/combination-sum/discuss/16502/A-general-approach-to-solution2-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partitioning)
        */
        std::vector<std::vector<int>> results;
        std::vector<int> empty;
        backtrack(nums, nums.size(), 0, empty, results, target);
        return results;
    }
    /*************************************************************/
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        return solution2(candidates, target);
    }
};
