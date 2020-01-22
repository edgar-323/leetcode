/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

class Solution {
private:
    int N;

    void recurse1(
            const int i,
            std::vector<int>& subset,
            std::vector<std::vector<int>>& results,
            const std::vector<int>& nums) {
        // Input `nums[]` is sorted

        // Include Current Subset
        results.push_back(subset);
        bool no_prev = true;
        int prev;
        for (int j = i; j < N; ++j) {
            if (no_prev or prev != nums[j]) {
                subset.push_back(nums[j]);
                recurse1(j+1, subset, results, nums);
                subset.pop_back();
                prev = nums[j];
                no_prev = false;
            }
        }
    }

    std::vector<std::vector<int>> solution1(std::vector<int>& nums) {
        N = nums.size();
        std::sort(nums.begin(), nums.end());
        auto results = std::vector<std::vector<int>>();
        auto subset = std::vector<int>();
        recurse1(0, subset, results, nums);

        return results; 
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
  		return solution1(nums);      
    }
};
