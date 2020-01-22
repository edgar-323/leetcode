/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
Each number in candidates may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]
*/
class Solution {
private:
    int N, target;
    
    void recurse1(const int i, const int curr_sum, std::vector<int>& curr_nums, const std::vector<int>& nums, std::vector<std::vector<int>>& results) {
        if (curr_sum == target) {
            results.push_back(curr_nums);
            return;
        }
        int prev = -1;
        for (int j = i; j < N; ++j) {
            if (nums[j] + curr_sum <= target and prev != nums[j]) {
                curr_nums.push_back(nums[j]);
                recurse1(j+1, curr_sum + nums[j], curr_nums, nums, results);
                curr_nums.pop_back();
                prev = nums[j];
            }
        }
    }

    std::vector<std::vector<int>> solution1(std::vector<int>& nums, const int target) {
        auto results = std::vector<std::vector<int>>();
        auto curr_nums = std::vector<int>();
        std::sort(nums.begin(), nums.end());
        N = nums.size();
        this->target = target;
        recurse1(0, 0, curr_nums, nums, results);

        return results;
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        return solution1(candidates, target);
    }
};
